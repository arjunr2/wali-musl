#include <stdlib.h>
#include <stdio.h>

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

/* User Main Function with args that clang generates */
int __main_argc_argv(int argc, char *argv[]);

/* Main void if not defined by clang (i.e, if the argument main is used) */
__attribute__((__weak__, nodebug))
int __main_void(void) {
  int argc = __cl_get_argc();
  char **argv = (char**) malloc(argc * sizeof(char*));
  if (argv == NULL) {
    return 1;
  }
  for (int i = 0; i < argc; i++) {
    int argv_len = __cl_get_argv_len(i);
    argv[i] = (char *) malloc(argv_len);
    if (argv[i] == NULL) {
      return 1;
    }
    __cl_copy_argv(argv[i], i);
  }
  return __main_argc_argv(argc, argv);
}
