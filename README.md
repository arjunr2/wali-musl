# Webassembly Linux Interface (Musl Libc)

This repo contains exploratory work towards creating a standard Linux syscall API for 
Webassembly. We build off of the base code of [musl libc](https://github.com/bminor/musl)

NOTE: We currently support only x86-64 and future work will include 
support for other architectures.

## Prerequisites

* [Clang](https://github.com/llvm/llvm-project/releases) is required for WASM compilation.
Download the clang+llvm package and add the `bin` directory to your PATH.
You may alternatively choose to build from source (which can take several hours) as directed 
[here](https://clang.llvm.org/get_started.html)

* [Webassembly Binary Toolkit](https://github.com/WebAssembly/wabt/releases)


## Building wali libc

The build/installation process mostly mirrors that of musl and is detailed in the 
[INSTALL](https://github.com/arjunr2/wali-musl/blob/master/INSTALL) file


## Compilation of C code
```shell
cd tests;
chmod +x compile-wali.sh
make
```

The above generates a "\*_link.wasm" output WASM executable for all C tests.
NOTE: We currently use the startup file out of WASI, but this will change in the future


## Running WASM code

Use a Webassembly runtime of your choice to execute the above generated WASM code 
with implementations of the imported "wali" methods. [WAMR](https://github.com/bytecodealliance/wasm-micro-runtime)
is easy to get started with details on implementing native functions [here](https://github.com/bytecodealliance/wasm-micro-runtime/blob/main/doc/export_native_api.md)


