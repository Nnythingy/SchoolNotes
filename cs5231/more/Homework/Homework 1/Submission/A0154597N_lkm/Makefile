# Makefile for compiling a loadable kernel module

PWD := $(shell pwd)
obj-m += hello_world_lkm.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
install:
	sudo make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules_install
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
