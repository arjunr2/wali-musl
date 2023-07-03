#include "atomic.h"
#include "init_env.h"

extern void __wasm_init_tp(void);

void __wali_call_ctors(void) __attribute((
  __import_module__("wali"),
  __import_name__("__call_ctors")
));
void __wali_call_dtors(void) __attribute((
  __import_module__("wali"),
  __import_name__("__call_dtors")
));

void __wali_proc_exit(int) __attribute((
  __import_module__("wali"),
  __import_name__("__proc_exit")
));

extern int __main_void(void);

__attribute__((export_name("_start")))
void _start(void) {
  static volatile int started = 0;
  if (a_cas(&started, 0, 1)) {
    __builtin_trap();
  }
  
  __wasm_init_tp();

  // The linker synthesizes this to call constructors.
  __wali_call_ctors();

  // Initialize environment variables from WALI
  init_env();

  // Call `__main_void` which will either be the application's zero-argument
  // `__main_void` function or a libc routine which obtains the command-line
  // arguments and calls `__main_argv_argc`.
  int r = __main_void();

  // Call atexit functions, destructors, stdio cleanup, etc.
  __wali_call_dtors();

  if (r != 0) {
      __wali_proc_exit(r);
  }
}
