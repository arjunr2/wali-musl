# Webassembly Linux Interface (Musl Libc)

This repo contains exploratory work towards creating a standard Linux syscall API for 
Webassembly. We build off of the base code of [musl libc](https://github.com/bminor/musl)

Refer to the parent [WALI](https://github.com/arjunr2/WALI) repository on a complete overview of using and testing WALI

NOTE: We currently support only x86-64 and future work will include 
support for other architectures.

## Prerequisites

* [Clang](https://github.com/llvm/llvm-project/releases?page=3) is required for WASM compilation (tested with 13.0.0).
Download the clang+llvm package and add the `bin` directory to your PATH.
You may alternatively choose to build from source (which can take several hours) as directed 
[here](https://clang.llvm.org/get_started.html)

* [Webassembly Binary Toolkit](https://github.com/WebAssembly/wabt/releases)


## Building wali libc

The build/installation process mostly mirrors that of musl and is detailed in the 
[INSTALL](https://github.com/arjunr2/wali-musl/blob/master/INSTALL) file.

NOTE: Currently, the build is tested with clang-13. Support for newer versions will be added. 


