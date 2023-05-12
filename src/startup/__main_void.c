#include <stdlib.h>
#include <stdio.h>

/* User Main Function with args that clang generates */
int __main_argc_argv(int argc, char *argv[]);

__attribute__((__weak__, nodebug))
int __main_void(void) {
  const char *test_str = "hello world";
  int argc = 5;
  char **argv = (char**) malloc(argc * sizeof(char*));
  for (int i = 0; i < argc; i++) {
    char *arg = (char*) malloc(80);
    sprintf(arg, "Arg%d", i);
    argv[i] = arg;
  }
  return __main_argc_argv(argc, argv);
}
