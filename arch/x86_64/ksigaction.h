#include <features.h>

struct __attribute__((packed)) k_sigaction {
	void (*handler)(int);
	unsigned long flags;
	void (*restorer)(void);
	unsigned mask[2];
};

hidden void __restore_rt() __attribute((
  __import_module__("wali"),
  __import_name__("__restore_rt")
));
#define __restore __restore_rt
