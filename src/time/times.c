#include <sys/times.h>
#include "syscall.h"

clock_t times(struct tms *tms)
{
	return __syscall_SYS_times(tms);
}
