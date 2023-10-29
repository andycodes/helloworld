
CFLAGS += -Isrc/arch 
CFLAGS += -Isrc/$(ARCH)

SSRC += src/arch/$(ARCH)/entry.s
SSRC += src/arch/$(ARCH)/trampoline.s
SSRC += src/arch/$(ARCH)/kernelvec.s
SSRC += src/arch/$(ARCH)/swtch.s

CSRC += src/arch/$(ARCH)/string.c
CSRC += src/arch/$(ARCH)/kalloc.c
CSRC += src/arch/$(ARCH)/proc.c
CSRC += src/arch/$(ARCH)/spinlock.c
CSRC += src/arch/$(ARCH)/sleeplock.c
CSRC += src/arch/$(ARCH)/uart.c
CSRC += src/arch/$(ARCH)/console.c
CSRC += src/arch/$(ARCH)/printf.c
CSRC += src/arch/$(ARCH)/start.c
CSRC += src/arch/$(ARCH)/main.c
CSRC += src/arch/$(ARCH)/virtio_disk.c
CSRC += src/arch/$(ARCH)/file.c
CSRC += src/arch/$(ARCH)/fs.c
CSRC += src/arch/$(ARCH)/vm.c
CSRC += src/arch/$(ARCH)/log.c
CSRC += src/arch/$(ARCH)/bio.c
CSRC += src/arch/$(ARCH)/plic.c
CSRC += src/arch/$(ARCH)/trap.c
CSRC += src/arch/$(ARCH)/pipe.c
CSRC += src/arch/$(ARCH)/syscall.c
CSRC += src/arch/$(ARCH)/sysfile.c
CSRC += src/arch/$(ARCH)/sysproc.c
CSRC += src/arch/$(ARCH)/exec.c