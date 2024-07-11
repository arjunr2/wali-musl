#ifndef _SYSCALL_DEFS_H_
#define _SYSCALL_DEFS_H_

#ifndef __scc
#define __scc(X) ((long) (X))
typedef long syscall_arg_t;
#endif

#define SYS_NULL 0

#define __SYSCALL_NARGS_X(a,b,c,d,e,f,g,h,n,...) n
#define __SYSCALL_NARGS(...) __SYSCALL_NARGS_X(__VA_ARGS__,7,6,5,4,3,2,1,0,)
#define __SYSCALL_CONCAT_X(a,b) a##b
#define __SYSCALL_CONCAT(a,b) __SYSCALL_CONCAT_X(a,b)
#define __SYSCALL_DISP(b,...) __SYSCALL_CONCAT(b,__SYSCALL_NARGS(__VA_ARGS__))(__VA_ARGS__)

#define syscall0(n) syscall(n)
#define syscall1(n,a) syscall(n,__scc(a))
#define syscall2(n,a,b) syscall(n,__scc(a),__scc(b))
#define syscall3(n,a,b,c) syscall(n,__scc(a),__scc(b),__scc(c))
#define syscall4(n,a,b,c,d) syscall(n,__scc(a),__scc(b),__scc(c),__scc(d))
#define syscall5(n,a,b,c,d,e) syscall(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e))
#define syscall6(n,a,b,c,d,e,f) syscall(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e),__scc(f))

#endif
