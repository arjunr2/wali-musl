extern _Thread_local struct __pthread __walilibc_pthread_self;

static inline uintptr_t __get_tp() {
  return (uintptr_t)&__walilibc_pthread_self;
}

/* Need to fix this for m/ucontext */
#define MC_PC __space[0]
