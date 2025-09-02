#include "atomic.h"
#include "init_env.h"

extern void __wasm_init_tp(void);

// Engine-internal initialization
void __wali_init(void) __attribute((
  __import_module__("wali"),
  __import_name__("__init")
));
// Engine-internal deinitialization
void __wali_deinit(void) __attribute((
  __import_module__("wali"),
  __import_name__("__deinit")
));

void __wali_proc_exit(int) __attribute((
  __import_module__("wali"),
  __import_name__("__proc_exit")
));

extern int __main_void(void);

// __wali_init must be run before any main or other exported functions
__attribute__((export_name("__wali_startup")))
void __wali_startup(void) {
  static volatile int started = 0;
  if (a_cas(&started, 0, 1)) {
    __builtin_trap();
  }
  
  __wali_init();
  __wasm_init_tp();
  // Initialize WALI environment variables
  init_env();
}

// __wali_cleanup must be run before exiting to cleanup any dangling state
__attribute__((export_name("__wali_cleanup")))
void __wali_cleanup(void) {
  __wali_deinit();
}

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
