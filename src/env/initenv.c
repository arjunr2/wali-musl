#include "init_env.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

#define FSIZE 1000

static int read_envfile(char *filename) {
  struct stat st;
  /* Check if env file exists */
  if (!access(filename, R_OK)) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) return WALI_ENV_READ_FAIL;

    if (fstat(fd, &st) < 0) {
      close(fd);
      return WALI_ENV_READ_FAIL;
    }
    int size = st.st_size;
    if (size == 0) {
      close(fd);
      return 0;
    }

    /* Map file into memory */
    char *envc = (char*) mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (envc == MAP_FAILED) {
      close(fd);
      return WALI_ENV_MALLOC_FAIL;
    }
    close(fd);

    char *start = envc;
    char *end = envc + size;
    char *curr = envc;

    /* Parse token by token */
    while (curr < end) {
      if (*curr == '\n') {
        *curr = '\0';
        if (putenv(strdup(start))) {
          munmap(envc, size);
          return WALI_ENV_READ_FAIL;
        }
        start = curr + 1;
      }
      curr++;
    }

    /* Handle last token if file doesn't end with newline */
    if (start < end) {
      size_t len = end - start;
      char *last = (char*) malloc(len + 1);
      if (!last) {
        munmap(envc, size);
        return WALI_ENV_MALLOC_FAIL;
      }
      memcpy(last, start, len);
      last[len] = '\0';

      if (putenv(last)) {
        free(last);
        munmap(envc, size);
        return WALI_ENV_READ_FAIL;
      }
    }

    /* Cleanup */
    munmap(envc, size);
  }
  return 0;
}

int init_env() {
  char filename[FSIZE];
  if (!filename) {
    return WALI_ENV_FILENAME_FAIL;
  }
  /* Populate env if file exists */
  int found = get_init_envfile(filename, FSIZE);
  if (found) {
    return read_envfile(filename);
  }
  return 0;
}

