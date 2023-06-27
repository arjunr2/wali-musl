#define _GNU_SOURCE
#include "pthread_impl.h"
#include "stdio_impl.h"
#include "libc.h"
#include "lock.h"
#include <sys/mman.h>
#include <string.h>
#include <stddef.h>

static void dummy_0()
{
}
weak_alias(dummy_0, __acquire_ptc);
weak_alias(dummy_0, __release_ptc);
weak_alias(dummy_0, __pthread_tsd_run_dtors);
weak_alias(dummy_0, __do_orphaned_stdio_locks);
weak_alias(dummy_0, __dl_thread_cleanup);
weak_alias(dummy_0, __membarrier_init);

static int tl_lock_count;
static int tl_lock_waiters;

void __tl_lock(void)
{
	int tid = __pthread_self()->tid;
	int val = __thread_list_lock;
	if (val == tid) {
		tl_lock_count++;
		return;
	}
	while ((val = a_cas(&__thread_list_lock, 0, tid)))
		__wait(&__thread_list_lock, &tl_lock_waiters, val, 0);
}

void __tl_unlock(void)
{
	if (tl_lock_count) {
		tl_lock_count--;
		return;
	}
	a_store(&__thread_list_lock, 0);
	if (tl_lock_waiters) __wake(&__thread_list_lock, 1, 0);
}

void __tl_sync(pthread_t td)
{
	a_barrier();
	int val = __thread_list_lock;
	if (!val) return;
	__wait(&__thread_list_lock, &tl_lock_waiters, val, 0);
	if (tl_lock_waiters) __wake(&__thread_list_lock, 1, 0);
}

_Noreturn void __pthread_exit(void *result)
{
	pthread_t self = __pthread_self();
	sigset_t set;

	self->canceldisable = 1;
	self->cancelasync = 0;
	self->result = result;

	while (self->cancelbuf) {
    char k[100] = "== CANCELBUF\n";
    write(1, k, strlen(k));
		void (*f)(void *) = self->cancelbuf->__f;
		void *x = self->cancelbuf->__x;
		self->cancelbuf = self->cancelbuf->__next;
		f(x);
	}

	__pthread_tsd_run_dtors();

	__block_app_sigs(&set);

	/* This atomic potentially competes with a concurrent pthread_detach
	 * call; the loser is responsible for freeing thread resources. */
	int state = a_cas(&self->detach_state, DT_JOINABLE, DT_EXITING);

	if (state==DT_DETACHED && self->map_base) {
		/* Since __unmapself bypasses the normal munmap code path,
		 * explicitly wait for vmlock holders first. This must be
		 * done before any locks are taken, to avoid lock ordering
		 * issues that could lead to deadlock. */
		__vm_wait();
	}


	/* Access to target the exiting thread with syscalls that use
	 * its kernel tid is controlled by killlock. For detached threads,
	 * any use past this point would have undefined behavior, but for
	 * joinable threads it's a valid usage that must be handled.
	 * Signals must be blocked since pthread_kill must be AS-safe. */
	LOCK(self->killlock);

	/* The thread list lock must be AS-safe, and thus depends on
	 * application signals being blocked above. */
	__tl_lock();

	/* If this is the only thread in the list, don't proceed with
	 * termination of the thread, but restore the previous lock and
	 * signal state to prepare for exit to call atexit handlers. */
	if (self->next == self) {
		__tl_unlock();
		UNLOCK(self->killlock);
		self->detach_state = state;
		__restore_sigs(&set);
		exit(0);
	}

	/* At this point we are committed to thread termination. */

	/* After the kernel thread exits, its tid may be reused. Clear it
	 * to prevent inadvertent use and inform functions that would use
	 * it that it's no longer available. At this point the killlock
	 * may be released, since functions that use it will consistently
	 * see the thread as having exited. Release it now so that no
	 * remaining locks (except thread list) are held if we end up
	 * resetting need_locks below. */
	self->tid = 0;
	UNLOCK(self->killlock);

	/* Process robust list in userspace to handle non-pshared mutexes
	 * and the detached thread case where the robust list head will
	 * be invalid when the kernel would process it. */
	__vm_lock();
	volatile void *volatile *rp;
	while ((rp=self->robust_list.head) && rp != &self->robust_list.head) {
		pthread_mutex_t *m = (void *)((char *)rp
			- offsetof(pthread_mutex_t, _m_next));
		int waiters = m->_m_waiters;
		int priv = (m->_m_type & 128) ^ 128;
		self->robust_list.pending = rp;
		self->robust_list.head = *rp;
		int cont = a_swap(&m->_m_lock, 0x40000000);
		self->robust_list.pending = 0;
		if (cont < 0 || waiters)
			__wake(&m->_m_lock, 1, priv);
	}
	__vm_unlock();

	__do_orphaned_stdio_locks();
	/* LDSO -- Not WALI supported */
  //__dl_thread_cleanup();

	/* Last, unlink thread from the list. This change will not be visible
	 * until the lock is released, which only happens after SYS_exit
	 * has been called, via the exit futex address pointing at the lock.
	 * This needs to happen after any possible calls to LOCK() that might
	 * skip locking if process appears single-threaded. */
	if (!--libc.threads_minus_1) libc.need_locks = -1;
	self->next->prev = self->prev;
	self->prev->next = self->next;
	self->prev = self->next = self;

  /* Linux creates thread with CLONE_CHILD_CLEARTID
  * Mirror unlocking performed by kernel by adding it here */
  __tl_unlock();

	if (state==DT_DETACHED && self->map_base) {
		/* Detached threads must block even implementation-internal
		 * signals, since they will not have a stack in their last
		 * moments of existence. */
		__block_all_sigs(&set);

		/* Robust list will no longer be valid, and was already
		 * processed above, so unregister it with the kernel. */
		if (self->robust_list.off)
			__syscall_SYS_set_robust_list(0, 3*sizeof(long));

    printf("== Detached Thread End: unmapself TBD\n");
		/* The following call unmaps the thread's stack mapping
		 * and then exits without touching the stack. */
		//__unmapself(self->map_base, self->map_size);
	}

	/* Wake any joiner. */
	a_store(&self->detach_state, DT_EXITED);
	__wake(&self->detach_state, 1, 1);

	for (;;) __syscall_SYS_exit(0);
}

void __do_cleanup_push(struct __ptcb *cb)
{
	struct pthread *self = __pthread_self();
	cb->__next = self->cancelbuf;
	self->cancelbuf = cb;
}

void __do_cleanup_pop(struct __ptcb *cb)
{
	__pthread_self()->cancelbuf = cb->__next;
}

struct start_args {
  /* Stack and TLS Base should be at the start of struct
  * This is expected since the startup function uses
  * offsets into this */
  void *stack;
  void *tls_base;
  /* */
	void *(*start_func)(void *);
	void *start_arg;
	volatile int control;
	unsigned long sig_mask[_NSIG/8/sizeof(long)];
};

//static int start(void *p)
//{
//	struct start_args *args = p;
//	int state = args->control;
//	if (state) {
//		if (a_cas(&args->control, 1, 2)==1)
//			__wait(&args->control, 0, 2, 1);
//		if (args->control) {
//			__syscall_SYS_set_tid_address(&args->control);
//			for (;;) __syscall_SYS_exit(0);
//		}
//	}
//	__syscall_SYS_rt_sigprocmask(SIG_SETMASK, &args->sig_mask, 0, _NSIG/8);
//	__pthread_exit(args->start_func(args->start_arg));
//	return 0;
//}
//
//static int start_c11(void *p)
//{
//	struct start_args *args = p;
//	int (*start)(void*) = (int(*)(void*)) args->start_func;
//	__pthread_exit((void *)(uintptr_t)start(args->start_arg));
//	return 0;
//}

void __wasm_thread_start_libc(int tid, void *p);
hidden void *__dummy_reference = __wasm_thread_start_libc;

/* Called by __wasm_thread_start_libc, written as an asm module */
hidden void __wasm_thread_start_libc_C(int tid, void *p) {
  struct start_args *args = p;
  pthread_t self = __pthread_self();
  /* pthread_create parent also races to set TID,
  * so use atomic_stores at both locations for whichever
  * writes first */
  a_store(&(self->tid), tid);
  /* Inherit parent signal mask */
  __syscall_SYS_rt_sigprocmask(SIG_SETMASK, &args->sig_mask, 0, _NSIG/8);
  /* User start function */
  __pthread_exit(args->start_func(args->start_arg));
}

#define ROUND(x) (((x)+PAGE_SIZE-1)&-PAGE_SIZE)

/* pthread_key_create.c overrides this */
static volatile size_t dummy = 0;
weak_alias(dummy, __pthread_tsd_size);
static void *dummy_tsd[1] = { 0 };
weak_alias(dummy_tsd, __pthread_tsd_main);

static FILE *volatile dummy_file = 0;
weak_alias(dummy_file, __stdin_used);
weak_alias(dummy_file, __stdout_used);
weak_alias(dummy_file, __stderr_used);

static void init_file_lock(FILE *f)
{
	if (f && f->lock<0) f->lock = 0;
}

int __pthread_create(pthread_t *restrict res, const pthread_attr_t *restrict attrp, void *(*entry)(void *), void *restrict arg)
{
	int ret, c11 = (attrp == __ATTRP_C11_THREAD);
	size_t size, guard;
	struct pthread *self, *new;
	unsigned char *map = 0, *stack = 0, *tsd = 0, *stack_limit;
	pthread_attr_t attr = { 0 };
	sigset_t set;

  size_t tls_align = __builtin_wasm_tls_align();
  size_t tls_size = __builtin_wasm_tls_size() + tls_align;
  void* tls_base = __builtin_wasm_tls_base();
  void* new_tls_base;
  size_t tls_offset;

	self = __pthread_self();
	if (!libc.threaded) {
		for (FILE *f=*__ofl_lock(); f; f=f->next)
			init_file_lock(f);
		__ofl_unlock();
		init_file_lock(__stdin_used);
		init_file_lock(__stdout_used);
		init_file_lock(__stderr_used);
		__syscall_SYS_rt_sigprocmask(SIG_UNBLOCK, SIGPT_SET, 0, _NSIG/8);
		self->tsd = (void **)__pthread_tsd_main;
		__membarrier_init();
		libc.threaded = 1;
	}
	if (attrp && !c11) attr = *attrp;

	__acquire_ptc();
	if (!attrp || c11) {
		attr._a_stacksize = __default_stacksize;
		attr._a_guardsize = __default_guardsize;
	}

	if (attr._a_stackaddr) {
		size_t need = tls_size + __pthread_tsd_size;
		size = attr._a_stacksize;
		stack = (void *)(attr._a_stackaddr & -16);
		stack_limit = (void *)(attr._a_stackaddr - size);
		/* Use application-provided stack for TLS only when
		 * it does not take more than ~12% or 2k of the
		 * application's stack space. */
		if (need < size/8 && need < 2048) {
			tsd = stack - __pthread_tsd_size;
			stack = tsd - tls_size;
			memset(stack, 0, need);
		} else {
			size = ROUND(need);
		}
		guard = 0;
	} else {
		guard = ROUND(attr._a_guardsize);
		size = guard + ROUND(attr._a_stacksize
			+ tls_size +  __pthread_tsd_size);
	}

	if (!tsd) {
		if (guard) {
			map = __mmap(0, size, PROT_NONE, MAP_PRIVATE|MAP_ANON, -1, 0);
			if (map == MAP_FAILED) goto fail;
			if (__mprotect(map+guard, size-guard, PROT_READ|PROT_WRITE)
			    && errno != ENOSYS) {
				__munmap(map, size);
				goto fail;
			}
		} else {
			map = __mmap(0, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANON, -1, 0);
			if (map == MAP_FAILED) goto fail;
		}
		tsd = map + size - __pthread_tsd_size;
		if (!stack) {
			stack = tsd - tls_size;
			stack_limit = map + guard;
		}
	}

  new_tls_base = __copy_tls(tsd - tls_size);
  tls_offset = new_tls_base - tls_base;
  /* Pthread structure for new thread */
  new = (void*)((uintptr_t)self + tls_offset);

	new->map_base = map;
	new->map_size = size;
	new->guard_size = guard;
	new->self = new;
	new->tsd = (void *)tsd;
	new->locale = &libc.global_locale;
	if (attr._a_detach) {
		new->detach_state = DT_DETACHED;
	} else {
		new->detach_state = DT_JOINABLE;
	}
	new->robust_list.head = &new->robust_list.head;
	new->canary = self->canary;
	new->sysinfo = self->sysinfo;

	/* Setup argument structure for the new thread on its stack.
	 * It's safe to access from the caller only until the thread
	 * list is unlocked. */
	//stack -= (uintptr_t)stack % sizeof(uintptr_t);
	//stack -= sizeof(struct start_args);
	//struct start_args *args = (void *)stack;
	//args->start_func = entry;
	//args->start_arg = arg;

  /* Setup argument and stack for new thread */
  /* Align stack to start_args */
  stack -= sizeof(struct start_args);
  stack -= (uintptr_t)stack % __alignof(struct start_args);
  struct start_args *args = (void*) stack;

  /* Align stack to 16 and set stack size */
  new->stack = (void*)((uintptr_t)stack & -16);
  new->stack_size = stack - stack_limit;
  /* asm trampoline */
  args->stack = new->stack;
  args->start_func = entry;
  args->start_arg = arg;
  args->tls_base = (void*)new_tls_base;
	args->control = attr._a_sched ? 1 : 0;

	/* Application signals (but not the synccall signal) must be
	 * blocked before the thread list lock can be taken, to ensure
	 * that the lock is AS-safe. */
	__block_app_sigs(&set);

	/* Ensure SIGCANCEL is unblocked in new thread. This requires
	 * working with a copy of the set so we can restore the
	 * original mask in the calling thread. */
	memcpy(&args->sig_mask, &set, sizeof args->sig_mask);
	args->sig_mask[(SIGCANCEL-1)/8/sizeof(long)] &=
		~(1UL<<((SIGCANCEL-1)%(8*sizeof(long))));

	__tl_lock();
	if (!libc.threads_minus_1++) libc.need_locks = 1;
	//ret = __clone((c11 ? start_c11 : start), stack, flags, args, &new->tid, TP_ADJ(new), &__thread_list_lock);
  
  /* Host call '__wasm_thread_spawn' creates host thread execution context
  * and calls the first argument for language specific start-up
  */

  //printf("TLS Base: %d | New TLS Base: %d\n", tls_base, new_tls_base);
  ret = __wasm_thread_spawn(__wasm_thread_start_libc, (void*) args);

	/* All clone failures translate to EAGAIN. If explicit scheduling
	 * was requested, attempt it before unlocking the thread list so
	 * that the failed thread is never exposed and so that we can
	 * clean up all transient resource usage before returning. */
	if (ret < 0) {
		ret = -EAGAIN;
	} else {
    a_store(&(new->tid), ret);
    if (attr._a_sched) {
      ret = __syscall_SYS_sched_setscheduler(
        new->tid, attr._a_policy, &attr._a_prio);
      if (a_swap(&args->control, ret ? 3 : 0)==2)
        __wake(&args->control, 1, 1);
      if (ret)
        __wait(&args->control, 0, 3, 0);
    }
	}

	if (ret >= 0) {
		new->next = self->next;
		new->prev = self;
		new->next->prev = new;
		new->prev->next = new;
	} else {
		if (!--libc.threads_minus_1) libc.need_locks = 0;
	}
	__tl_unlock();
	__restore_sigs(&set);
	__release_ptc();

	if (ret < 0) {
		if (map) __munmap(map, size);
		return -ret;
	}

	*res = new;
	return 0;
fail:
	__release_ptc();
	return EAGAIN;
}

weak_alias(__pthread_exit, pthread_exit);
weak_alias(__pthread_create, pthread_create);
