#include <unistd.h>
#include "syscall.h"

gid_t getgid(void)
{
	return __syscall_SYS_getgid();
}
