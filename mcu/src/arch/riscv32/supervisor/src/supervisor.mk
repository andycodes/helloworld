SUPERVISOR_PATH ?= src/arch/$(ARCH)/supervisor

CFLAGS += -I$(SUPERVISOR_PATH)/include  -Wno-pointer-to-int-cast

#SSRC += $(SUPERVISOR_PATH)/src/usys.s

CSRC += $(SUPERVISOR_PATH)/src/console.c
CSRC += $(SUPERVISOR_PATH)/src/main.c
CSRC += $(SUPERVISOR_PATH)/src/printf.c 
CSRC += $(SUPERVISOR_PATH)/src/uart.c 