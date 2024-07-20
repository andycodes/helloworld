# Makefile for embedded development

# Compiler and tools
PREFIX = aarch64-none-elf-

AS = $(PREFIX)as
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
SIZE = $(PREFIX)size
NM = $(PREFIX)nm
READELF = readelf

# Directories
SRCDIR = .
BUILDDIR = build
INCDIR = ./

# Source files
#C_SOURCES = $(wildcard $(SRCDIR)/*.c)
#ASM_SOURCES = $(wildcard $(SRCDIR)/*.s)

C_SOURCES_FILE = kernel.c
ASM_SOURCES_FILE = boot.s 

C_SOURCES = $(patsubst %,./%,$(C_SOURCES_FILE))
ASM_SOURCES = $(patsubst %,./%,$(ASM_SOURCES_FILE))

$(info "!!!!THE CUR BOARD is $(C_SOURCES)")

# Object files
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(C_SOURCES)) \
          $(patsubst $(SRCDIR)/%.s, $(BUILDDIR)/%.o, $(ASM_SOURCES))

# Executable
TARGET = $(BUILDDIR)/output.elf

# Compiler flags
CFLAGS =  -fno-builtin -nostdlib -nostartfiles -ffreestanding -Wall -g -I$(INCDIR)
LDFLAGS = -T plat.ld

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LDFLAGS) -o $@

# Compile C files
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Assemble assembly files
$(BUILDDIR)/%.o: $(SRCDIR)/%.s
	@mkdir -p $(BUILDDIR)
	$(AS) -c $< -o $@

# Clean the build directory
clean:
	rm -rf $(BUILDDIR)

# Print the current directory
current_dir:
	@echo "Current path: $(shell pwd)"

# Dependencies
-include $(OBJECTS:.o=.d)

.PHONY: all clean current_dir
