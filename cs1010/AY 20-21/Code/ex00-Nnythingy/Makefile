.SILENT: test
CC=clang
LDLIBS=-lm -lcs1010
INCLUDEDIR=~/libcs1010/include

CFLAGS=-g @.warnings -I $(INCLUDEDIR) -L $(LIBDIR)
LIBDIR=~/libcs1010/lib

all: test

test: echo divide quadratic
	./test.sh echo 4
	./test.sh divide 4
	./test.sh quadratic 4

clean:
	rm echo divide quadratic
# vim:noexpandtab
