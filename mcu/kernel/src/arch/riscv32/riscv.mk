

CFLAGS += -Isrc/arch/$(ARCH)  -Wno-pointer-to-int-cast

SSRC += src/arch/$(ARCH)/start.s 
SSRC += src/arch/$(ARCH)/sys.s

CSRC += src/arch/$(ARCH)/lib.c 
CSRC += src/arch/$(ARCH)/os.c
CSRC += src/arch/$(ARCH)/task.c 
CSRC += src/arch/$(ARCH)/user.c
