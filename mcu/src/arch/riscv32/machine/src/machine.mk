MACHINE_PATH ?= src/arch/$(ARCH)/machine

CFLAGS += -I$(MACHINE_PATH)/include  -Wno-pointer-to-int-cast

SSRC += $(MACHINE_PATH)/src/entry.s 
SSRC += $(MACHINE_PATH)/src/sys.s
SSRC += $(MACHINE_PATH)/src/mem.s
SSRC += $(MACHINE_PATH)/src/usys.s

CSRC += $(MACHINE_PATH)/src/start.c
CSRC += $(MACHINE_PATH)/src/alloc.c
CSRC += $(MACHINE_PATH)/src/lib.c 
CSRC += $(MACHINE_PATH)/src/os.c
CSRC += $(MACHINE_PATH)/src/task.c 
CSRC += $(MACHINE_PATH)/src/user.c
CSRC += $(MACHINE_PATH)/src/timer.c
CSRC += $(MACHINE_PATH)/src/trap.c
CSRC += $(MACHINE_PATH)/src/lock.c
CSRC += $(MACHINE_PATH)/src/plic.c
CSRC += $(MACHINE_PATH)/src/syscall.c
