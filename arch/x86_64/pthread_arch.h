/*
static inline uintptr_t __get_tp()
{
	uintptr_t tp;
	__asm__ ("mov %%fs:0,%0" : "=r" (tp) );
	return tp;
}
*/
uintptr_t __get_tp()  __attribute((
  __import_name__("__get_tp")
));

#define MC_PC gregs[REG_RIP]
