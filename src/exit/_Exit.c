#include <stdlib.h>
#include "syscall.h"

_Noreturn void _Exit(int ec)
{
	__syscall_SYS_exit_group(ec);
	for (;;) __syscall_SYS_exit(ec);
}
