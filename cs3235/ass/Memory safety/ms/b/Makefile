.PHONY: all clean

all: b

b: b.c
	gcc b.c -o b -g -Wno-format-security -fno-stack-protector

clean:
	rm b
