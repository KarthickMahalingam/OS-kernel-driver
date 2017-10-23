#Makefile
obj-m   := fuses.o
KDIR    := /lib/modules/`uname -r`/build
all:    
	make -C $(KDIR) SUBDIRS=`pwd` modules
clean:  
	make -C $(KDIR) SUBDIRS=`pwd` clean
install:
	sudo insmod fuses.ko
uninstall:
	sudo rmmod fuses
