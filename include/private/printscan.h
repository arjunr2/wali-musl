#ifndef _PRINTSCAN_H_
#define _PRINTSCAN_H_

#if defined(__wali_printscan_enable_long_double)

// Full long double support.
typedef long double long_double_pr_t;

#else

#include <stdio.h>

typedef double long_double_pr_t;
#undef LDBL_TRUE_MIN
#define LDBL_TRUE_MIN DBL_DENORM_MIN
#undef LDBL_MIN
#define LDBL_MIN DBL_MIN
#undef LDBL_MAX
#define LDBL_MAX DBL_MAX
#undef LDBL_EPSILON
#define LDBL_EPSILON DBL_EPSILON
#undef LDBL_MANT_DIG
#define LDBL_MANT_DIG DBL_MANT_DIG
#undef LDBL_MIN_EXP
#define LDBL_MIN_EXP DBL_MIN_EXP
#undef LDBL_MAX_EXP
#define LDBL_MAX_EXP DBL_MAX_EXP
#undef LDBL_DIG
#define LDBL_DIG DBL_DIG
#undef LDBL_MIN_10_EXP
#define LDBL_MIN_10_EXP DBL_MIN_10_EXP
#undef LDBL_MAX_10_EXP
#define LDBL_MAX_10_EXP DBL_MAX_10_EXP
#undef frexpl
#define frexpl(x, exp) frexp(x, exp)
#undef copysignl
#define copysignl(x, y) copysign(x, y)
#undef fmodl
#define fmodl(x, y) fmod(x, y)
#undef scalbnl
#define scalbnl(arg, exp) scalbn(arg, exp)
__attribute__((__cold__, __noreturn__))
static void long_double_not_supported(void) {
    void abort(void) __attribute__((__noreturn__));
    fputs("Support for formatting long double values is currently disabled.\n"
          "To enable it, remove define \'__wali_printscan_enable_long_double\'\n", &__stderr_FILE);
    abort();
}

#endif

#endif
