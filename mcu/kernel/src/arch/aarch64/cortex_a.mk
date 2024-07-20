
ARM_PATH ?= src/arch/aarch64

CFLAGS += -I$(ARM_PATH)

SSRC += $(ARM_PATH)/boot.s
CSRC += $(ARM_PATH)/kernel.c 
