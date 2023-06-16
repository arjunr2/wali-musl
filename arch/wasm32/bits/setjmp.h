/* Set jmpbuf to max size across all supported archs
* x86_64, aarch64, riscv64 */
typedef unsigned long __jmp_buf[26];
