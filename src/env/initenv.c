#include "init_env.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define FSIZE 1000

static void read_envfile(char *filename) {
  struct stat st;
  /* Check if env file exists */
  if (!access(filename, R_OK)) {
    int fd = open(filename, O_RDONLY);
    int status = fstat(fd, &st);
    int size = st.st_size;

    /* Read file into list */
    char *envc = (char*) malloc(size + 1);
    if (envc) {
      char *token;
      char *env_tok = envc;
      const char s[2] = "\n";
      /* Read file contents */
      read(fd, envc, size);
      envc[size] = 0;
      /* Parse token by token */
      token = strtok(env_tok, s);
      while (token != NULL) {
        if (putenv(strdup(token))) {
          printf("Error in reading environ file \'%s\'\n", filename);
          break;
        }
        token = strtok(NULL, s);
      }
      /* Cleanup */
      free(envc);
    } else {
      printf("Failed to malloc for env\n");
    }
  } 
}

void init_env() {
  char filename[FSIZE];
  if (!filename) {
    printf("Failed to malloc for envfile\n");
  }

  /* Populate env if file exists */
  int found = get_init_envfile(filename, FSIZE);
  if (found) {
    read_envfile(filename);
  }
}

