#include <unistd.h>
#include "syscall.h"

gid_t getegid(void)
{
	return __syscall_SYS_getegid();
}
