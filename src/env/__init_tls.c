#define SYSCALL_NO_TLS 1
#include <elf.h>
#include <limits.h>
#include <sys/mman.h>
#include <string.h>
#include <stddef.h>
#include "pthread_impl.h"
#include "libc.h"
#include "atomic.h"
#include "syscall.h"

volatile int __thread_list_lock;

void __wasm_init_tp() {
  __init_tp((void*)__get_tp());
}

int __init_tp(void *p)
{
	pthread_t td = p;
	td->self = td;
	//int r = __set_thread_area(TP_ADJ(p));
	//if (r < 0) return -1;
  //if (!r) libc.can_do_threads = 1;
	libc.can_do_threads = 1;
	td->detach_state = DT_JOINABLE;
	td->tid = __syscall_SYS_set_tid_address(&__thread_list_lock);
	td->locale = &libc.global_locale;
	td->robust_list.head = &td->robust_list.head;
	td->sysinfo = __sysinfo;
	td->next = td->prev = td;
	return 0;
}

static struct builtin_tls {
	char c;
	struct pthread pt;
	void *space[16];
} builtin_tls[1];
#define MIN_TLS_ALIGN offsetof(struct builtin_tls, pt)

static struct tls_module main_tls;

/* __wasm_init_tls is a LLVM compiler-builtin
* Linked in with wasm32-wasi-threads */
extern void __wasm_init_tls(void*);

/* Set alignment and initialize the WASM TLS */
void *__copy_tls(unsigned char *mem) {
  size_t tls_align = __builtin_wasm_tls_align();
  volatile void* tls_base = __builtin_wasm_tls_base();
  mem += tls_align;
  mem -= (uintptr_t)mem & (tls_align-1);
  __wasm_init_tls(mem);
  /* __wasm_init_tls modifies the tls_base global 
  * in assumption that it is to be used for a new thread
  * Reset tls_base back to our current thread tls_base */
  __asm__("local.get %0\n"
              "global.set __tls_base\n"
              :: "r"(tls_base));
  return mem;
}

#if ULONG_MAX == 0xffffffff
typedef Elf32_Phdr Phdr;
#else
typedef Elf64_Phdr Phdr;
#endif

extern weak hidden const size_t _DYNAMIC[];

static void static_init_tls(size_t *aux)
{
	unsigned char *p;
	size_t n;
	Phdr *phdr, *tls_phdr=0;
	size_t base = 0;
	void *mem;

	for (p=(void *)aux[AT_PHDR],n=aux[AT_PHNUM]; n; n--,p+=aux[AT_PHENT]) {
		phdr = (void *)p;
		if (phdr->p_type == PT_PHDR)
			base = aux[AT_PHDR] - phdr->p_vaddr;
		if (phdr->p_type == PT_DYNAMIC && _DYNAMIC)
			base = (size_t)_DYNAMIC - phdr->p_vaddr;
		if (phdr->p_type == PT_TLS)
			tls_phdr = phdr;
		if (phdr->p_type == PT_GNU_STACK &&
		    phdr->p_memsz > __default_stacksize)
			__default_stacksize =
				phdr->p_memsz < DEFAULT_STACK_MAX ?
				phdr->p_memsz : DEFAULT_STACK_MAX;
	}

	if (tls_phdr) {
		main_tls.image = (void *)(base + tls_phdr->p_vaddr);
		main_tls.len = tls_phdr->p_filesz;
		main_tls.size = tls_phdr->p_memsz;
		main_tls.align = tls_phdr->p_align;
		libc.tls_cnt = 1;
		libc.tls_head = &main_tls;
	}

	main_tls.size += (-main_tls.size - (uintptr_t)main_tls.image)
		& (main_tls.align-1);
#ifdef TLS_ABOVE_TP
	main_tls.offset = GAP_ABOVE_TP;
	main_tls.offset += (-GAP_ABOVE_TP + (uintptr_t)main_tls.image)
		& (main_tls.align-1);
#else
	main_tls.offset = main_tls.size;
#endif
	if (main_tls.align < MIN_TLS_ALIGN) main_tls.align = MIN_TLS_ALIGN;

	libc.tls_align = main_tls.align;
	libc.tls_size = 2*sizeof(void *) + sizeof(struct pthread)
#ifdef TLS_ABOVE_TP
		+ main_tls.offset
#endif
		+ main_tls.size + main_tls.align
		+ MIN_TLS_ALIGN-1 & -MIN_TLS_ALIGN;

	if (libc.tls_size > sizeof builtin_tls) {
#ifndef SYS_mmap2
#define SYS_mmap2 SYS_mmap
#endif
		mem = (void *)__syscall_var(
			SYS_mmap2,
			0, libc.tls_size, PROT_READ|PROT_WRITE,
			MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
		/* -4095...-1 cast to void * will crash on dereference anyway,
		 * so don't bloat the init code checking for error codes and
		 * explicitly calling a_crash(). */
	} else {
		mem = builtin_tls;
	}

	/* Failure to initialize thread pointer is always fatal. */
	if (__init_tp(__copy_tls(mem)) < 0)
		a_crash();
}

weak_alias(static_init_tls, __init_tls);
