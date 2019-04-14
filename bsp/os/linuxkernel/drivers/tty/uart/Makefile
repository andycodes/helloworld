
mymodule-objs := uart.o

ifeq ($(arch),arm)

obj-m := $(mymodule-objs)

PWD := $(shell pwd)

KDIR := /project/mini6410_linux_kernel/linux-2.6.38 

all:

	$(MAKE) -C $(KDIR) M=$(PWD)
	@echo $(arch)
	
##########################################################################################3

else

ifneq ($(KERNELRELEASE),)

#kbuild syntax. dependency relationshsip of files and target modules are listed here.

obj-m := $(mymodule-objs)

else

PWD := $(shell pwd)

KVER ?= $(shell uname -r)

KDIR := /lib/modules/$(KVER)/build

all:

	$(MAKE) -C $(KDIR) M=$(PWD)

	
endif

endif

clean:

	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.ko  *.mod.* *.bak  *.symvers *.order