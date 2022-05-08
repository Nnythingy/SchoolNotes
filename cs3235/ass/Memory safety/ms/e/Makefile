.PHONY: all clean

all: e

e: e.c tmalloc.c tmalloc.h
	gcc -m32 -o e e.c tmalloc.c -g -fno-stack-protector -z execstack

clean:
	rm e
