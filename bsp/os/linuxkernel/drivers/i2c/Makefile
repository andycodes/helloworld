CONFIG_MODULE_SIG=n


ifneq ($(KERNELRELEASE),)
	mymodule-objs := i2c.o
	obj-m := $(mymodule-objs) 
else
	PWD := $(shell pwd)
	KDIR := /lib/modules/$(shell uname -r)/build
default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
	rm -rf .*.cmd *.o *.mod.c *.ko .tmp_versions *.ko  *.mod.* *.bak  *.symvers *.order
endif