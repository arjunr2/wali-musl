#ifndef ERRNO_H
#define ERRNO_H

#include "../../include/errno.h"

#ifdef __GNUC__
__attribute__((const))
#endif
hidden int *___errno_location(void);
int __errno_process = 0;

#undef errno
#define errno (*___errno_location())

#endif
