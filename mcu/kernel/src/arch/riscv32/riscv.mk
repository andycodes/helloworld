

CFLAGS += -Isrc/arch/$(ARCH)/include  -Wno-pointer-to-int-cast

SSRC += src/arch/$(ARCH)/entry.s 
SSRC += src/arch/$(ARCH)/sys.s
SSRC += src/arch/$(ARCH)/mem.s
SSRC += src/arch/$(ARCH)/usys.s

CSRC += src/arch/$(ARCH)/start.c
CSRC += src/arch/$(ARCH)/alloc.c
CSRC += src/arch/$(ARCH)/lib.c 
CSRC += src/arch/$(ARCH)/os.c
CSRC += src/arch/$(ARCH)/task.c 
CSRC += src/arch/$(ARCH)/user.c
CSRC += src/arch/$(ARCH)/timer.c
CSRC += src/arch/$(ARCH)/trap.c
CSRC += src/arch/$(ARCH)/lock.c
CSRC += src/arch/$(ARCH)/plic.c
CSRC += src/arch/$(ARCH)/syscall.c
