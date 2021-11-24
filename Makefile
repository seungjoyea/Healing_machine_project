obj-m := hello_drv.o
KDIR := /home/jo/linux_kernel/
PWD := $(shell pwd)
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
	$(CROSS_COMPILE)gcc /home/jo/hello_drv/hello_test.c -o hello_test.elf
	scp *.ko ecube@172.30.1.8:/home/ecube/ecube_jo
	scp *.elf ecube@172.30.1.8:/home/ecube/ecube_jo

clean:
	-rm -f *.o *.mod.c .*.cmd modules.order Module.symvers
	rm -f *.o
