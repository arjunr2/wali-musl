
#define a_cas a_cas
static int a_cas(volatile int *p, int t, int s) {
  __sync_val_compare_and_swap(p, t, s);
  return t;
}

#define a_crash a_crash
static void a_crash() { __builtin_trap(); }

#define a_ctz_64 a_ctz_64
static int a_ctz_64(uint64_t x) {
  return __builtin_ctzll(x);
}

#define a_clz_64 a_clz_64
static int a_clz_64(uint64_t x) {
  return __builtin_clzll(x);
}

#define a_clz_32 __builtin_clz
#define a_ctz_32 __builtin_ctz

#define a_swap a_swap
static int a_swap(volatile int *p, int v) {
  __sync_swap(p, v);
  return v;
}

#define a_and a_and
static void a_and(volatile int *p, int v) {
  __atomic_and_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_or a_or
static void a_or(volatile int *p, int v) {
  __atomic_or_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_and_64 a_and_64
static void a_and_64(volatile uint64_t *p, uint64_t v) {
  __atomic_and_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_or_64 a_or_64
static void a_or_64(volatile uint64_t *p, uint64_t v) {
  __atomic_or_fetch(p, v, __ATOMIC_SEQ_CST);
}

#define a_inc a_inc
static void a_inc(volatile int *p) {
  __atomic_add_fetch(p, 1, __ATOMIC_SEQ_CST);
}

#define a_dec a_dec
static void a_dec(volatile int *p) {
  __atomic_sub_fetch(p, 1, __ATOMIC_SEQ_CST);
}

#define a_store a_store
static void a_store(volatile int *p, int x) {
  __atomic_store_n (p, x, __ATOMIC_SEQ_CST);
}

#define a_fetch_add a_fetch_add
static int a_fetch_add(volatile int *p, int v) {
  __atomic_fetch_add(p, v, __ATOMIC_SEQ_CST);
}


//#define a_cas_p a_cas_p
//void *a_cas_p(volatile void *p, void *t, void *s) {
//  __atomic_compare_exchange(p, t, s, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
//  return t;
//}
//));

#define a_cas_p a_cas_p
void *a_cas_p(volatile void *p, void *t, void *s)
__attribute((
  __import_module__("wali"),
  __import_name__("a_cas_p")
));


#define a_barrier a_barrier
void a_barrier()
__attribute((
  __import_module__("wali"),
  __import_name__("a_barrier")
));

#define a_spin a_spin
void a_spin()
__attribute((
  __import_module__("wali"),
  __import_name__("a_spin")
));

