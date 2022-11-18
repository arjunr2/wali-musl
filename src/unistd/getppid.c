#include <unistd.h>
#include "syscall.h"

pid_t getppid(void)
{
	return __syscall_SYS_getppid();
}
