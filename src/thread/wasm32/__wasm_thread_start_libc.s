	.text

	.export_name	__wasm_thread_start_libc, __wasm_thread_start_libc

	.globaltype	__stack_pointer, i32
	.globaltype	__tls_base, i32
	.functype	__wasm_thread_start_libc_C (i32, i32) -> ()

	.hidden	__wasm_thread_start_libc
	.globl	__wasm_thread_start_libc
	.type	__wasm_thread_start_libc,@function

__wasm_thread_start_libc:
	.functype	__wasm_thread_start_libc (i32, i32) -> ()

	# Set up the minimum C environment.
  # Start arg must have 
  #   offsetof(start_arg, stack) = 0
  #   offsetof(start_arg, tls_base) = 4
	local.get   1  # start_arg
	i32.load    0  # stack
	global.set  __stack_pointer

	local.get   1  # start_arg
	i32.load    4  # tls_base
	global.set  __tls_base

	# Make the C function do the rest of work.
	local.get   0  # tid
	local.get   1  # start_arg
	call __wasm_thread_start_libc_C

	end_function
