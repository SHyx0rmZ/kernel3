OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386:x86-64)

SECTIONS
{
	. = 0x101000;

	.text : {
		*(.module_entry)
		*(.text)
		*(.module_exit)
	}
	.data : {
		*(.data)
	}
	.rodata : {
		*(.rodata)
	}
	.bss : {
		*(.bss)
	}
}
