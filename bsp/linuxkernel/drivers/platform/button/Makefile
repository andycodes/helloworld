ifneq ($(KERNELRELEASE),)

#kbuild syntax. dependency relationshsip of files and target modules are listed here.

module-objs := button_drv.o

obj-m := $(module-objs)

else

PWD := $(shell pwd)
CC = $(shell which arm-linux-gcc)

# the src root dir
# kernel dir
KDIR := /project/share/trunck

all:

	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:

	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.ko  *.mod.* *.bak  *.symvers *.order

endif