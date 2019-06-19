MEMORY { 
	rom : ORIGIN = 0x00, LENGTH = 0x2000 
}
SECTIONS {
	ROM : 
	{ 
		head.o (.text)
		*(.text) 
	} >rom
	. = 0x3000;
	.bss ALIGN(4) : { *(.bss) *(COMMON) }
	. = 0x4000;
	.data ALIGN(4) : AT(0x8000){ *(.data) }
	_end = .;
} 


 
