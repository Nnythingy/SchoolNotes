.PHONY: all clean

all: a

a: a.c
	gcc a.c -o a -g -fno-stack-protector -z execstack

clean:
	rm a
