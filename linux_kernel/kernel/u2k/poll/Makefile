obj-m := cdata.o
KVERSION := $(shell uname -r)
DEVICE="cdata"
KDIR := /lib/modules/$(KVERSION)/build
PWD := $(shell pwd)


default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
test: 
	gcc -o test test.c
load:
	sudo sh load.cdata.sh
unload:
	sudo sh unload.cdata.sh
clean:
	rm -rf *.o *.ko .*cmd modules.* Module.* .tmp_versions *.mod.c test main-loop control
show:
	ls -l /dev/$(DEVICE); lsmod | grep $(DEVICE)
