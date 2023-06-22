/* TRAP */
#define a_crash a_crash
static void __attribute__((noinline)) a_crash() { __builtin_trap(); }

/* CTZ and CLZ 32/64 bit */
#define a_ctz_64 a_ctz_64
static int __attribute__((noinline)) a_ctz_64(uint64_t x) {
  return __builtin_ctzll(x);
}
#define a_ctz_32 a_ctz_32
static int __attribute__((noinline)) a_ctz_32(int x) {
  return __builtin_ctz(x);
}

#define a_clz_64 a_clz_64
static int __attribute__((noinline)) a_clz_64(uint64_t x) {
  return __builtin_clzll(x);
}
#define a_clz_32 a_clz_32
static int __attribute__((noinline)) a_clz_32(int x) {
  return __builtin_clz(x);
}

/* CAS and Swap */
#define a_cas a_cas
static int __attribute__((noinline)) a_cas(volatile int *p, int t, int s) {
  return __sync_val_compare_and_swap(p, t, s);
}

#define a_swap a_swap
static int __attribute__((noinline)) a_swap(volatile int *p, int v) {
  return __sync_swap(p, v);
}

#define a_and a_and
static void __attribute__((noinline)) a_and(volatile int *p, int v) {
  __atomic_and_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_or a_or
/* WAMR has a bug with O0 when using __atomic_or_fetch */
static void __attribute__((noinline)) a_or(volatile int *p, int v) {
  //__asm__ __volatile__ ("local.get %0\n"
  //        "local.get %1\n"
  //        "i32.atomic.rmw.or 0\n"
  //        :: "r"(p), "r"(v));
  __atomic_or_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_and_64 a_and_64
static void __attribute__((noinline)) a_and_64(volatile uint64_t *p, uint64_t v) {
  __atomic_and_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_or_64 a_or_64
static void __attribute__((noinline)) a_or_64(volatile uint64_t *p, uint64_t v) {
  __atomic_or_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_inc a_inc
static void __attribute__((noinline)) a_inc(volatile int *p) {
  __atomic_add_fetch(p, 1, __ATOMIC_SEQ_CST);
}

#define a_dec a_dec
static void __attribute__((noinline)) a_dec(volatile int *p) {
  __atomic_sub_fetch(p, 1, __ATOMIC_SEQ_CST);
}


#define a_store a_store
static void __attribute__((noinline)) a_store(volatile int *p, int x) {
  __atomic_store_n (p, x, __ATOMIC_SEQ_CST);
}

#define a_fetch_add a_fetch_add
static int __attribute__((noinline)) a_fetch_add(volatile int *p, int v) {
  return __atomic_fetch_add (p, v, __ATOMIC_SEQ_CST);
}


#define a_cas_p a_cas_p
void *a_cas_p(volatile void *p, void *t, void *s)
__attribute((
  __import_module__("wali"),
  __import_name__("a_cas_p")
));
//static void* __attribute__((noinline)) a_cas_p(volatile void *p, void *t, void *s) {
//  __atomic_compare_exchange(p, t, s, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
//  return t;
//}

