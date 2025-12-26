extern int __main_void(void);
extern int __wali_startup(void);
extern int __wali_cleanup(void);

void __wali_proc_exit(int) __attribute((
  __import_module__("wali"),
  __import_name__("__proc_exit")
));

__attribute__((export_name("_start")))
void _start(void) {
  // Return code for exit
  int r;
  r = __wali_startup();
  if (r) {
    goto exit_label;
  }
  // Call `__main_void` which will either be the application's zero-argument
  // `__main_void` function or a libc routine which obtains the command-line
  // arguments and calls `__main_argv_argc`.
  r = __main_void();
  if (r) {
    goto exit_label;
  }
  int s = __wali_cleanup();
  if (s) {
    // Update the reutrn code with cleanup's error, if it has one
    r = s;
  }
exit_label:
  __wali_proc_exit(r);
}
