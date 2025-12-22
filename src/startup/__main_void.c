#include <stdlib.h>
#include <stdio.h>
#include "init_env.h"
#include "atomic.h"

/* Command Line Argument handling for WALI */
int __cl_get_argc(void) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_get_argc")
));

int __cl_get_argv_len(int) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_get_argv_len")
));

int __cl_copy_argv(char*, int) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_copy_argv")
));

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

extern void __wasm_init_tp(void);

/* Export startup methods */
// __wali_init must be run before any main or other exported functions
//
// This is called by default in `crt`, but is exported for users to 
// explicitly call if using -nostartfiles
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
//
// This is called by default in `crt`, but is exported for users to 
// explicitly call if using -nostartfiles
void __wali_cleanup(void) {
  __wali_deinit();
}


/* User Main Function with args that clang generates */
int __main_argc_argv(int argc, char *argv[]);

/* Main void if not defined by clang (i.e, if the argument main is used) */
__attribute__((__weak__, nodebug))
int __main_void(void) {
  int argc = __cl_get_argc();
  char **argv = (char**) malloc((argc+1) * sizeof(char*));
  if (argv == NULL) {
    return 1;
  }
  for (int i = 0; i < argc; i++) {
    int argv_len = __cl_get_argv_len(i);
    argv[i] = (char *) malloc(argv_len+1);
    if (argv[i] == NULL) {
      return 1;
    }
    __cl_copy_argv(argv[i], i);
  }
  argv[argc] = NULL;
  return __main_argc_argv(argc, argv);
}
