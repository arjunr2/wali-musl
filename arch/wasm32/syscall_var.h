#ifndef _SYSCALL_VAR_H
#define _SYSCALL_VAR_H
#include <stdio.h>

#define CASE_SYSCALL(name, ...) \
  case SYS_##name: return __syscall_SYS_##name(__VA_ARGS__); break; 

/* Internal syscall implementation for non-const syscall NR invocation */
static long __syscall_var(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
  switch(n) {
		CASE_SYSCALL (read, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (write, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (open, (char*)a1,(int)a2,(int)a3);
		CASE_SYSCALL (close, (int)a1);
		CASE_SYSCALL (stat, (char*)a1,(void*)a2);
		CASE_SYSCALL (fstat, (int)a1,(void*)a2);
		CASE_SYSCALL (lstat, (char*)a1,(void*)a2);
		CASE_SYSCALL (poll, (void*)a1,(unsigned long long)a2,(int)a3);
		CASE_SYSCALL (lseek, (int)a1,(long long)a2,(int)a3);
		CASE_SYSCALL (mmap, (void*)a1,(unsigned int)a2,(int)a3,(int)a4,(int)a5,(long long)a6);
		CASE_SYSCALL (mprotect, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (munmap, (void*)a1,(unsigned int)a2);
		CASE_SYSCALL (brk, (void*)a1);
		CASE_SYSCALL (rt_sigaction, (int)a1,(void*)a2,(void*)a3,(unsigned int)a4);
		CASE_SYSCALL (rt_sigprocmask, (int)a1,(void*)a2,(void*)a3,(unsigned int)a4);
		CASE_SYSCALL (rt_sigreturn, (long)a1);
		CASE_SYSCALL (ioctl, (int)a1,(int)a2,(char*)a3);
		CASE_SYSCALL (pread64, (int)a1,(char*)a2,(unsigned int)a3,(long long)a4);
		CASE_SYSCALL (pwrite64, (int)a1,(char*)a2,(unsigned int)a3,(long long)a4);
		CASE_SYSCALL (readv, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (writev, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (access, (char*)a1,(int)a2);
		CASE_SYSCALL (pipe, (int*)a1);
		CASE_SYSCALL (select, (int)a1,(void*)a2,(void*)a3,(void*)a4,(void*)a5);
		CASE_SYSCALL (sched_yield, );
		CASE_SYSCALL (mremap, (void*)a1,(unsigned int)a2,(unsigned int)a3,(int)a4,(void*)a5);
		CASE_SYSCALL (msync, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (madvise, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (dup, (int)a1);
		CASE_SYSCALL (dup2, (int)a1,(int)a2);
		CASE_SYSCALL (nanosleep, (void*)a1,(void*)a2);
		CASE_SYSCALL (alarm, (int)a1);
		CASE_SYSCALL (setitimer, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (getpid, );
		CASE_SYSCALL (socket, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (connect, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (accept, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (sendto, (int)a1,(void*)a2,(unsigned int)a3,(int)a4,(void*)a5,(unsigned int)a6);
		CASE_SYSCALL (recvfrom, (int)a1,(void*)a2,(unsigned int)a3,(int)a4,(void*)a5,(void*)a6);
		CASE_SYSCALL (sendmsg, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (recvmsg, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (shutdown, (int)a1,(int)a2);
		CASE_SYSCALL (bind, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (listen, (int)a1,(int)a2);
		CASE_SYSCALL (getsockname, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (getpeername, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (socketpair, (int)a1,(int)a2,(int)a3,(int*)a4);
		CASE_SYSCALL (setsockopt, (int)a1,(int)a2,(int)a3,(void*)a4,(unsigned int)a5);
		CASE_SYSCALL (getsockopt, (int)a1,(int)a2,(int)a3,(void*)a4,(void*)a5);
		CASE_SYSCALL (fork, );
		CASE_SYSCALL (execve, (char*)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (exit, (int)a1);
		CASE_SYSCALL (wait4, (int)a1,(int*)a2,(int)a3,(void*)a4);
		CASE_SYSCALL (kill, (int)a1,(int)a2);
		CASE_SYSCALL (uname, (void*)a1);
		CASE_SYSCALL (fcntl, (int)a1,(int)a2,(unsigned long)a3);
		CASE_SYSCALL (flock, (int)a1,(int)a2);
		CASE_SYSCALL (fsync, (int)a1);
		CASE_SYSCALL (fdatasync, (int)a1);
		CASE_SYSCALL (ftruncate, (int)a1,(long long)a2);
		CASE_SYSCALL (getcwd, (char*)a1,(unsigned int)a2);
		CASE_SYSCALL (chdir, (char*)a1);
		CASE_SYSCALL (fchdir, (int)a1);
		CASE_SYSCALL (rename, (char*)a1,(char*)a2);
		CASE_SYSCALL (mkdir, (char*)a1,(int)a2);
		CASE_SYSCALL (rmdir, (char*)a1);
		CASE_SYSCALL (link, (char*)a1,(char*)a2);
		CASE_SYSCALL (unlink, (char*)a1);
		CASE_SYSCALL (symlink, (char*)a1,(char*)a2);
		CASE_SYSCALL (readlink, (char*)a1,(char*)a2,(unsigned int)a3);
		CASE_SYSCALL (chmod, (char*)a1,(int)a2);
		CASE_SYSCALL (fchmod, (int)a1,(int)a2);
		CASE_SYSCALL (chown, (char*)a1,(int)a2,(int)a3);
		CASE_SYSCALL (fchown, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (umask, (int)a1);
		CASE_SYSCALL (gettimeofday, (void*)a1,(void*)a2);
		CASE_SYSCALL (getrlimit, (int)a1,(void*)a2);
		CASE_SYSCALL (getrusage, (int)a1,(void*)a2);
		CASE_SYSCALL (sysinfo, (void*)a1);
		CASE_SYSCALL (getuid, );
		CASE_SYSCALL (getgid, );
		CASE_SYSCALL (setuid, (int)a1);
		CASE_SYSCALL (setgid, (int)a1);
		CASE_SYSCALL (geteuid, );
		CASE_SYSCALL (getegid, );
		CASE_SYSCALL (setpgid, (int)a1,(int)a2);
		CASE_SYSCALL (getppid, );
		CASE_SYSCALL (setsid, );
		CASE_SYSCALL (setreuid, (int)a1,(int)a2);
		CASE_SYSCALL (setregid, (int)a1,(int)a2);
		CASE_SYSCALL (getgroups, (unsigned int)a1,(void*)a2);
		CASE_SYSCALL (setgroups, (unsigned int)a1,(void*)a2);
		CASE_SYSCALL (setresuid, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (setresgid, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (getpgid, (int)a1);
		CASE_SYSCALL (getsid, (int)a1);
		CASE_SYSCALL (rt_sigpending, (void*)a1,(unsigned int)a2);
		CASE_SYSCALL (rt_sigsuspend, (void*)a1,(unsigned int)a2);
		CASE_SYSCALL (sigaltstack, (void*)a1,(void*)a2);
		CASE_SYSCALL (statfs, (char*)a1,(void*)a2);
		CASE_SYSCALL (fstatfs, (int)a1,(void*)a2);
		CASE_SYSCALL (prctl, (int)a1,(unsigned long)a2,(unsigned long)a3,(unsigned long)a4,(unsigned long)a5);
		CASE_SYSCALL (setrlimit, (int)a1,(void*)a2);
		CASE_SYSCALL (chroot, (char*)a1);
		CASE_SYSCALL (gettid, );
		CASE_SYSCALL (tkill, (int)a1,(int)a2);
		CASE_SYSCALL (futex, (int*)a1,(int)a2,(int)a3,(void*)a4,(int*)a5,(int)a6);
		CASE_SYSCALL (sched_getaffinity, (int)a1,(unsigned int)a2,(void*)a3);
		CASE_SYSCALL (getdents64, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (set_tid_address, (int*)a1);
		CASE_SYSCALL (fadvise, (int)a1,(long long)a2,(long long)a3,(int)a4);
		CASE_SYSCALL (clock_gettime, (int)a1,(void*)a2);
		CASE_SYSCALL (clock_getres, (int)a1,(void*)a2);
		CASE_SYSCALL (clock_nanosleep, (int)a1,(int)a2,(void*)a3,(void*)a4);
		CASE_SYSCALL (exit_group, (int)a1);
		CASE_SYSCALL (epoll_ctl, (int)a1,(int)a2,(int)a3,(void*)a4);
		CASE_SYSCALL (openat, (int)a1,(char*)a2,(int)a3,(int)a4);
		CASE_SYSCALL (mkdirat, (int)a1,(char*)a2,(int)a3);
		CASE_SYSCALL (fchownat, (int)a1,(char*)a2,(int)a3,(int)a4,(int)a5);
		CASE_SYSCALL (newfstatat, (int)a1,(char*)a2,(void*)a3,(int)a4);
		CASE_SYSCALL (unlinkat, (int)a1,(char*)a2,(int)a3);
		CASE_SYSCALL (linkat, (int)a1,(char*)a2,(int)a3,(char*)a4,(int)a5);
		CASE_SYSCALL (symlinkat, (char*)a1,(int)a2,(char*)a3);
		CASE_SYSCALL (readlinkat, (int)a1,(char*)a2,(char*)a3,(unsigned int)a4);
		CASE_SYSCALL (fchmodat, (int)a1,(char*)a2,(int)a3,(int)a4);
		CASE_SYSCALL (faccessat, (int)a1,(char*)a2,(int)a3,(int)a4);
		CASE_SYSCALL (pselect6, (int)a1,(void*)a2,(void*)a3,(void*)a4,(void*)a5,(void*)a6);
		CASE_SYSCALL (ppoll, (void*)a1,(unsigned long long)a2,(void*)a3,(void*)a4,(unsigned int)a5);
		CASE_SYSCALL (utimensat, (int)a1,(char*)a2,(void*)a3,(int)a4);
		CASE_SYSCALL (epoll_pwait, (int)a1,(void*)a2,(int)a3,(int)a4,(void*)a5,(unsigned int)a6);
		CASE_SYSCALL (eventfd, (int)a1);
		CASE_SYSCALL (accept4, (int)a1,(void*)a2,(void*)a3,(int)a4);
		CASE_SYSCALL (eventfd2, (int)a1,(int)a2);
		CASE_SYSCALL (epoll_create1, (int)a1);
		CASE_SYSCALL (dup3, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (pipe2, (int*)a1,(int)a2);
		CASE_SYSCALL (prlimit64, (int)a1,(int)a2,(void*)a3,(void*)a4);
		CASE_SYSCALL (renameat2, (int)a1,(char*)a2,(int)a3,(char*)a4,(int)a5);
		CASE_SYSCALL (getrandom, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (statx, (int)a1,(char*)a2,(int)a3,(unsigned int)a4,(void*)a5);
		CASE_SYSCALL (faccessat2, (int)a1,(char*)a2,(int)a3,(int)a4);
    default: {
      printf("Invalid syscall var call -- NR %d\n",  n);
      return -ENOSYS;
    }
  }
}

#endif
