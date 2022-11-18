#include <unistd.h>
#include "syscall.h"

uid_t geteuid(void)
{
	return __syscall_SYS_geteuid();
}
