#ifndef _FENV_H
#define _FENV_H

#ifdef __cplusplus
extern "C" {
#endif

#include <bits/fenv.h>

int feclearexcept(int) __attribute((
  __import_name__("feclearexcept")
));

int fegetexceptflag(fexcept_t *, int) __attribute((
  __import_name__("fegetexceptflag")
));

int feraiseexcept(int) __attribute((
  __import_name__("feraiseexcept")
));

int fesetexceptflag(const fexcept_t *, int) __attribute((
  __import_name__("fesetexceptflag")
));

int fetestexcept(int) __attribute((
  __import_name__("fetestexcept")
));


int fegetround(void) __attribute((
  __import_name__("fegetround")
));

int fesetround(int) __attribute((
  __import_name__("fesetround")
));


int fegetenv(fenv_t *) __attribute((
  __import_name__("fegetenv")
));

int feholdexcept(fenv_t *) __attribute((
  __import_name__("feholdexcept")
));

int fesetenv(const fenv_t *) __attribute((
  __import_name__("fesetenv")
));

int feupdateenv(const fenv_t *) __attribute((
  __import_name__("feupdateenv")
));


#ifdef __cplusplus
}
#endif
#endif

