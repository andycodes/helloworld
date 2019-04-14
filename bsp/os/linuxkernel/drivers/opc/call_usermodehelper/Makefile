ifneq ($(KERNELRELEASE),)

#kbuild syntax. dependency relationshsip of files and target modules are listed here.

mymodule-objs := usermodehelper.o

obj-m := $(mymodule-objs)

else

PWD := $(shell pwd)

KVER ?= $(shell uname -r)

KDIR := /lib/modules/$(KVER)/build

all:

	$(MAKE) -C $(KDIR) M=$(PWD)

clean:

	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.ko  *.mod.* *.bak  *.symvers *.order

endif