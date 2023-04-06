#include <errno.h>
#include <stdio.h>
#include "pthread_impl.h"

int __errno_process = 0;
int *__errno_location(void)
{
	//return &__pthread_self()->errno_val;
  //printf("-- WARNING -- Setting Errno\n");
  return &__errno_process;
}

weak_alias(__errno_location, ___errno_location);
