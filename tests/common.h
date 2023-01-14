#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int print(char* buf) {
  int len = strlen(buf);
  write(1, buf, len);
  return len;
}

int print_int(long val) {
  char res[12];
  int len = 0;
  while (val > 0) {
    res[len++] = (val % 10) + '0';
    val /= 10;
  }
  res[len] = 0;

  for (int j = 0; j < len/2; j++) {
    char k = res[j];
    res[j] = res[len-1-j];
    res[len-1-j] = k;
  }

  write(1, res, len);
  return len;
}

#define PRINT_INT(hd, int_val) {  \
  print(hd ":    ");  \
  print_int(int_val); \
  print("\n");  \
}
#define PRINT_STR(hd, str_val) {  \
  print(hd ":    ");  \
  print(str_val); \
  print("\n");  \
} 
