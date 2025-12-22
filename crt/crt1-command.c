extern int __main_void(void);
extern void __wali_startup(void);
extern void __wali_cleanup(void);

void __wali_proc_exit(int) __attribute((
  __import_module__("wali"),
  __import_name__("__proc_exit")
));

__attribute__((export_name("_start")))
void _start(void) {
  __wali_startup();
  // Call `__main_void` which will either be the application's zero-argument
  // `__main_void` function or a libc routine which obtains the command-line
  // arguments and calls `__main_argv_argc`.
  int r = __main_void();
  __wali_cleanup();
  __wali_proc_exit(r);
}
