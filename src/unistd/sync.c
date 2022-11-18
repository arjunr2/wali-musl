#include <unistd.h>
#include "syscall.h"

void sync(void)
{
	__syscall_SYS_sync();
}
