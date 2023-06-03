#include "pthread_impl.h"
#include <threads.h>

_Thread_local struct pthread __walilibc_pthread_self;

static pthread_t __pthread_self_internal()
{
	return __pthread_self();
}

weak_alias(__pthread_self_internal, pthread_self);
weak_alias(__pthread_self_internal, thrd_current);
