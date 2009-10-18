OUTPUT_FORMAT(binary)
OUTPUT_ARCH(i386)

SECTIONS
{
	. = 0x100020;

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
