.PHONY: clean all

SRC_C:=$(wildcard *.c)
SRC_O:=$(SRC_C:.c=_link.o)

default: all

all: $(SRC_O)

%_link.o: %.c
	echo $(SRC_O)
	./compile-wali.sh $<

clean:
	rm *.wasm
	rm *.wat
	rm *.ll
