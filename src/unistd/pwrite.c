#include <unistd.h>
#include "syscall.h"

ssize_t pwrite(int fd, const void *buf, size_t size, off_t ofs)
{
	return syscall_cp(SYS_pwrite64, fd, buf, size, __SYSCALL_LL_PRW(ofs));
}
