#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char **copy_environ() {
  int ct = 4;
  char **envp = (char**) malloc(ct * sizeof(char*));
  int i = 0;
  for (char **e = __environ; *e; e++, i++) {
    if (i == (ct-1)) {
      ct *= 2;
      envp = realloc(envp, ct * sizeof(char*));
    }
    envp[i] = strdup(*e);
  }
  envp[i] = NULL;
  return envp;
}
