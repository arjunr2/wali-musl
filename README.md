# Webassembly Linux Interface (Libc)

This repo contains exploratory work towards creating a standard Linux syscall API for 
Webassembly. We repurpose the base code of [musl libc](https://github.com/bminor/musl)

NOTE: We currently support only x86-64 and future work will include 
support for other architectures.

## Building wali libc


## Compilation of C code


## Running WASM code

Use a Webassembly runtime of your choice to execute the above generated WASM code 
with implementations of the imported "wali" methods. [WAMR](https://github.com/bytecodealliance/wasm-micro-runtime)
is easy to get started with details on implementing native functions [here](https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/export_native_api.md)


