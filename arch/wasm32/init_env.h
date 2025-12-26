// Use codes greater than 255 for failure so 
// WALI can tell this apart from main exit codes
enum {
  WALI_STARTUP_FAIL = 257,
  WALI_CLEANUP_FAIL = 258,
  WALI_ENV_READ_FAIL = 259,
  WALI_ENV_FILENAME_FAIL = 260,
  WALI_ENV_MALLOC_FAIL = 261,
};

int init_env(void);

/* Command Line Argument handling for WALI */
int __cl_get_argc(void) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_get_argc")
));

int __cl_get_argv_len(int) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_get_argv_len")
));

int __cl_copy_argv(char*, int) __attribute ((
  __import_module__("wali"),
  __import_name__("__cl_copy_argv")
));

// Engine-internal initialization
int __wali_init(void) __attribute((
  __import_module__("wali"),
  __import_name__("__init")
));
// Engine-internal deinitialization
int __wali_deinit(void) __attribute((
  __import_module__("wali"),
  __import_name__("__deinit")
));


int get_init_envfile(char* filebuf, int fsize) __attribute ((
  __import_module__("wali"),
  __import_name__("__get_init_envfile")
));
