#!/bin/bash

sysroot_dir=../sysroot
crtfile=startup/crt1.o 
file=$(basename $1 .c)

clang --target=wasm32 --sysroot=$sysroot_dir $file.c -S -emit-llvm -o $file.ll -v
llc $file.ll -filetype=obj -o $file.wasm
wasm2wat $file.wasm -o $file.wat
wasm-ld --no-entry --allow-undefined -L$sysroot_dir/lib $file.wasm $crtfile -lc -o ${file}_link.wasm
wasm2wat ${file}_link.wasm -o ${file}_link.wat
