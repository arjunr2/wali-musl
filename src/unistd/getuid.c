#include <unistd.h>
#include "syscall.h"

uid_t getuid(void)
{
	return __syscall_SYS_getuid();
}
