# Webassembly Linux Interface (Musl Libc)

This repo contains exploratory work towards creating a standard Linux syscall API for 
Webassembly. We build off of the base code of [musl libc](https://github.com/bminor/musl)

Refer to the parent [WALI](https://github.com/arjunr2/WALI) repository on a complete overview of using and testing WALI

NOTE: We currently support x86-64, aarch64, and riscv64 architectures. Future work will expand support

## Prerequisites

* Custom [clang](https://github.com/llvm/llvm-project/releases?page=3) is required for WALI compilation.
Build llvm as shown in parent WALI directory, and add the `bin` directory to your PATH.

* [Webassembly Binary Toolkit](https://github.com/WebAssembly/wabt/releases)


## Building wali libc

The Makefile in parent [WALI](https://github.com/arjunr2/WALI) allows building this with a simple `make libc` command.
Under the hood, this makefile generates the appropriate `config.mak` and build flags
If the WALI compiler is installed independently, substitute appropriate variables into `config.mak` for your use-case

## Unsupported libc features
- timer\_create; must figure out SIGEV\_SIGNAL notification
