.PHONY: all clean

all: d

d: d.c
	gcc d.c -o d -g -fno-stack-protector -z execstack

clean:
	rm d
