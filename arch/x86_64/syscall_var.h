#ifndef _SYSCALL_VAR_H
#define _SYSCALL_VAR_H

#define CASE_SYSCALL(name, fn_name, ...) \
  case SYS_##name: return __syscall_SYS_##fn_name(__VA_ARGS__); break; 

/* Internal syscall implementation for non-const syscall NR invocation */
static long __syscall_var(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
  switch(n) {
		CASE_SYSCALL (read, read, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (write, write, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (open, open, (char*)a1,(int)a2,(int)a3);
		CASE_SYSCALL (close, close, (int)a1);
		CASE_SYSCALL (stat, stat, (char*)a1,(void*)a2);
		CASE_SYSCALL (fstat, fstat, (int)a1,(void*)a2);
		CASE_SYSCALL (lstat, lstat, (char*)a1,(void*)a2);
		CASE_SYSCALL (poll, poll, (void*)a1,(int)a2,(int)a3);
		CASE_SYSCALL (lseek, lseek, (int)a1,(long long)a2,(int)a3);
		CASE_SYSCALL (mmap, mmap, (void*)a1,(unsigned int)a2,(int)a3,(int)a4,(int)a5,(long long)a6);
		CASE_SYSCALL (mprotect, mprotect, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (munmap, munmap, (void*)a1,(unsigned int)a2);
		CASE_SYSCALL (brk, brk, (void*)a1);
		CASE_SYSCALL (rt_sigaction, rt_sigaction, (int)a1,(void*)a2,(void*)a3,(unsigned int)a4);
		CASE_SYSCALL (rt_sigprocmask, rt_sigprocmask, (int)a1,(void*)a2,(void*)a3,(unsigned int)a4);
		CASE_SYSCALL (rt_sigreturn, rt_sigreturn, (long)a1);
		CASE_SYSCALL (ioctl, ioctl, (int)a1,(int)a2,(char*)a3);
		CASE_SYSCALL (pread64, pread64, (int)a1,(void*)a2,(unsigned int)a3,(long long)a4);
		CASE_SYSCALL (pwrite64, pwrite64, (int)a1,(void*)a2,(unsigned int)a3,(long long)a4);
		CASE_SYSCALL (readv, readv, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (writev, writev, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (access, access, (char*)a1,(int)a2);
		CASE_SYSCALL (pipe, pipe, (int*)a1);
		CASE_SYSCALL (select, select, (int)a1,(void*)a2,(void*)a3,(void*)a4,(void*)a5);
		CASE_SYSCALL (sched_yield, sched_yield, );
		CASE_SYSCALL (mremap, mremap, (void*)a1,(unsigned int)a2,(unsigned int)a3,(int)a4,a5);
		CASE_SYSCALL (msync, msync, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (madvise, madvise, (void*)a1,(unsigned int)a2,(int)a3);
		CASE_SYSCALL (dup, dup, (int)a1);
		CASE_SYSCALL (dup2, dup2, (int)a1,(int)a2);
		CASE_SYSCALL (nanosleep, nanosleep, (void*)a1,(void*)a2);
		CASE_SYSCALL (alarm, alarm, (int)a1);
		CASE_SYSCALL (getpid, getpid, );
		CASE_SYSCALL (socket, socket, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (connect, connect, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (accept, accept, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (sendto, sendto, (int)a1,(void*)a2,(unsigned int)a3,(int)a4);
		CASE_SYSCALL (recvfrom, recvfrom, (int)a1,(void*)a2,(unsigned int)a3,(int)a4,(void*)a5,(void*)a6);
		CASE_SYSCALL (sendmsg, sendmsg, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (recvmsg, recvmsg, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (shutdown, shutdown, (int)a1,(int)a2);
		CASE_SYSCALL (bind, bind, (int)a1,(void*)a2,(unsigned int)a3);
		CASE_SYSCALL (listen, listen, (int)a1,(int)a2);
		CASE_SYSCALL (getsockname, getsockname, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (getpeername, getpeername, (int)a1,(void*)a2,(void*)a3);
		CASE_SYSCALL (setsockopt, setsockopt, (int)a1,(int)a2,(int)a3,(void*)a4,(unsigned int)a5);
		CASE_SYSCALL (getsockopt, getsockopt, (int)a1,(int)a2,(int)a3,(void*)a4,(void*)a5);
		CASE_SYSCALL (fork, fork, );
		CASE_SYSCALL (execve, execve, (char*)a1,(char*)a2,(char*)a3);
		CASE_SYSCALL (exit, exit, (int)a1);
		CASE_SYSCALL (wait4, wait4, (int)a1,(int*)a2,(int)a3,(void*)a4);
		CASE_SYSCALL (kill, kill, (int)a1,(int)a2);
		CASE_SYSCALL (uname, uname, (void*)a1);
		CASE_SYSCALL (fcntl, fcntl, (int)a1,(int)a2,a3);
		CASE_SYSCALL (flock, flock, (int)a1,(int)a2);
		CASE_SYSCALL (fsync, fsync, (int)a1);
		CASE_SYSCALL (ftruncate, ftruncate, (int)a1,(long long)a2);
		CASE_SYSCALL (getcwd, getcwd, (char*)a1,(unsigned int)a2);
		CASE_SYSCALL (chdir, chdir, (char*)a1);
		CASE_SYSCALL (mkdir, mkdir, (char*)a1,(int)a2);
		CASE_SYSCALL (rmdir, rmdir, (char*)a1);
		CASE_SYSCALL (link, link, (char*)a1,(char*)a2);
		CASE_SYSCALL (unlink, unlink, (char*)a1);
		CASE_SYSCALL (symlink, symlink, (char*)a1,(char*)a2);
		CASE_SYSCALL (readlink, readlink, (char*)a1,(char*)a2,(unsigned int)a3);
		CASE_SYSCALL (chmod, chmod, (char*)a1,(int)a2);
		CASE_SYSCALL (fchmod, fchmod, (int)a1,(int)a2);
		CASE_SYSCALL (chown, chown, (char*)a1,(int)a2,(int)a3);
		CASE_SYSCALL (fchown, fchown, (int)a1,(int)a2,(int)a3);
		CASE_SYSCALL (umask, umask, (int)a1);
		CASE_SYSCALL (getuid, getuid, );
		CASE_SYSCALL (getgid, getgid, );
		CASE_SYSCALL (geteuid, geteuid, );
		CASE_SYSCALL (getegid, getegid, );
		CASE_SYSCALL (setpgid, setpgid, (int)a1,(int)a2);
		CASE_SYSCALL (getppid, getppid, );
		CASE_SYSCALL (setsid, setsid, );
		CASE_SYSCALL (getpgid, getpgid, (int)a1);
		CASE_SYSCALL (getsid, getsid, (int)a1);
		CASE_SYSCALL (rt_sigsuspend, rt_sigsuspend, (void*)a1,(unsigned int)a2);
		CASE_SYSCALL (sigaltstack, sigaltstack, (void*)a1,(void*)a2);
		CASE_SYSCALL (utime, utime, (char*)a1,(void*)a2);
		CASE_SYSCALL (statfs, statfs, (char*)a1,(void*)a2);
		CASE_SYSCALL (fstatfs, fstatfs, (int)a1,(void*)a2);
		CASE_SYSCALL (getdents64, getdents64, (int)a1,(void*)a2,(int)a3);
		CASE_SYSCALL (fadvise, fadvise, (int)a1,(long long)a2,(long long)a3,(int)a4);
		CASE_SYSCALL (clock_gettime, clock_gettime, (int)a1,(void*)a2);
		CASE_SYSCALL (clock_nanosleep, clock_nanosleep, (int)a1,(int)a2,(void*)a3,(void*)a4);
		CASE_SYSCALL (exit_group, exit_group, (int)a1);
		CASE_SYSCALL (openat, openat, (int)a1,(char*)a2,(int)a3,(int)a4);
		CASE_SYSCALL (unlinkat, unlinkat, (int)a1,(char*)a2,(int)a3);
		CASE_SYSCALL (faccessat, faccessat, (int)a1,(char*)a2,(int)a3,(int)a4);
		CASE_SYSCALL (utimensat, utimensat, (int)a1,(char*)a2,(void*)a3,(int)a4);
		CASE_SYSCALL (eventfd, eventfd, (int)a1);
		CASE_SYSCALL (eventfd2, eventfd2, (int)a1,(int)a2);
		CASE_SYSCALL (pipe2, pipe2, (int*)a1,(int)a2);
		CASE_SYSCALL (statx, statx, (int)a1,(char*)a2,(int)a3,(int)a4,(void*)a5);
    default: return -1;
  }
}

#endif
