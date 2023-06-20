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

#define syscall_vararg0(n) syscall_vararg_wrapper(n)
#define syscall_vararg1(n,a) syscall_vararg_wrapper(n,__scc(a))
#define syscall_vararg2(n,a,b) syscall_vararg_wrapper(n,__scc(a),__scc(b))
#define syscall_vararg3(n,a,b,c) syscall_vararg_wrapper(n,__scc(a),__scc(b),__scc(c))
#define syscall_vararg4(n,a,b,c,d) syscall_vararg_wrapper(n,__scc(a),__scc(b),__scc(c),__scc(d))
#define syscall_vararg5(n,a,b,c,d,e) syscall_vararg_wrapper(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e))
#define syscall_vararg6(n,a,b,c,d,e,f) syscall_vararg_wrapper(n,__scc(a),__scc(b),__scc(c),__scc(d),__scc(e),__scc(f))


#endif
