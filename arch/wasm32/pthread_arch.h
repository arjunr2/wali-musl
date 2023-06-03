extern _Thread_local struct __pthread __walilibc_pthread_self;

static inline uintptr_t __get_tp() {
  return (uintptr_t)&__walilibc_pthread_self;
}

#define MC_PC gregs[REG_RIP]

