#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "syscall.h"
#include "libc.h"

struct ctx {
	int id, eid, sid;
	int nr, ret;
};

#define DO_SETXID(xid,...) \
static void do_set##xid(void *p) {  \
	struct ctx *c = p;  \
	if (c->ret<0) return; \
	int ret = __syscall_cp(SYS_set##xid, __VA_ARGS__);  \
	if (ret && !c->ret) { \
		/* If one thread fails to set ids after another has already \
		 * succeeded, forcibly killing the process is the only safe \
		 * thing to do. State is inconsistent and dangerous. Use  \
		 * SIGKILL because it is uncatchable. */  \
		__block_all_sigs(0);  \
		__syscall_SYS_kill(__syscall_SYS_getpid(), SIGKILL);  \
	} \
	c->ret = ret; \
}

DO_SETXID(resuid, c->id, c->eid, c->sid)
DO_SETXID(uid, c->id)
DO_SETXID(resgid, c->id, c->eid, c->sid)
DO_SETXID(gid, c->id)
DO_SETXID(reuid, c->id, c->eid)
DO_SETXID(regid, c->id, c->eid)


int __setxid(int nr, int id, int eid, int sid)
{
	/* ret is initially nonzero so that failure of the first thread does not
	 * trigger the safety kill above. */
	struct ctx c = { .nr = nr, .id = id, .eid = eid, .sid = sid, .ret = 1 };
  void (*do_setxid)(void *);

#define DO_SETXID_CALLBACK(xid,...) \
  case SYS_set##xid: do_setxid = do_set##xid; break;

  switch (nr) {
    DO_SETXID_CALLBACK(resuid);
    DO_SETXID_CALLBACK(resgid);
    DO_SETXID_CALLBACK(regid);
    DO_SETXID_CALLBACK(uid);
    DO_SETXID_CALLBACK(gid);
    DO_SETXID_CALLBACK(reuid);
    default: 
      printf("Unsupported SETXID syscall: %d\n", nr); 
      do_setxid = NULL;
  }
  if (do_setxid) {
	  __synccall(do_setxid, &c);
  } else {
    c.ret = -ENOSYS;
  }
	return __syscall_ret(c.ret);
}
