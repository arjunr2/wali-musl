.PHONY: dir clean all

CC=gcc

WASM_DIR=wasm
ELF_DIR=elf

SRC_C:=$(wildcard *.c)
SRC_O:=$(SRC_C:.c=.o)
SRC_WASM:=$(SRC_C.c=.wasm)

all: dir $(SRC_O)

dir:
	mkdir -p $(WASM_DIR)
	mkdir -p $(ELF_DIR)

%.o: %.c
	./compile-wali.sh -o $(WASM_DIR) $<
	$(CC) -o $(ELF_DIR)/$* $<


clean:
	rm -r $(WASM_DIR)
	rm -r $(ELF_DIR)
