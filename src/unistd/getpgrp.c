#include <unistd.h>
#include "syscall.h"

pid_t getpgrp(void)
{
	return __syscall_SYS_getpgid(0);
}
