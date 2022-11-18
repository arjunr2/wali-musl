#include <threads.h>
#include "syscall.h"

void thrd_yield()
{
	__syscall_SYS_sched_yield();
}
