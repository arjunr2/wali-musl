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

int main()
{
    struct stat sb;
    char path[] = "compile-wali.sh";

    if (fstatat(AT_FDCWD, path, &sb, 0) == -1) {
        print("ERROR\n");
    }
    print_int(sizeof(long));
    print("\n");
    print_int((char*)(&sb.st_ino) - (char*)(&sb));
    print("\n");

    print("ID of containing device: [");
    print_int((uintmax_t) major(sb.st_dev));
    print(",");
    print_int((uintmax_t) minor(sb.st_dev));
    print("]\n");

    print("File type:                ");

    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  print("block device\n");            break;
    case S_IFCHR:  print("character device\n");        break;
    case S_IFDIR:  print("directory\n");               break;
    case S_IFIFO:  print("FIFO/pipe\n");               break;
    case S_IFLNK:  print("symlink\n");                 break;
    case S_IFREG:  print("regular file\n");            break;
    case S_IFSOCK: print("socket\n");                  break;
    default:       print("unknown?\n");                break;
    }

    #define PRINT(hd, int_val) {  \
      print(hd ":    ");  \
      print_int(int_val); \
      print("\n");  \
    }
    #define PRINT_STR(hd, str_val) {  \
      print(hd ":    ");  \
      print(str_val); \
      print("\n");  \
    } 
    PRINT("I-node number", (uintmax_t) sb.st_ino);
    PRINT("Mode", (uintmax_t) sb.st_mode);
    PRINT("Link count", (uintmax_t) sb.st_nlink);
    PRINT("UID", (uintmax_t) sb.st_uid);
    PRINT("GID", (uintmax_t) sb.st_gid);
    PRINT("Preferred I/O block size", (intmax_t) sb.st_blksize);
    PRINT("File size", (intmax_t) sb.st_size);
    PRINT("Blocks allocated", (intmax_t) sb.st_blocks);
    PRINT("Last status change", sb.st_ctime);
    PRINT("Last file access", sb.st_atime);
    PRINT("Last file modification", sb.st_mtime);

    //exit(EXIT_SUCCESS);
}
