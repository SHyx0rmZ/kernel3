NUKE_VIRTUAL_ADDRESS equ 0x100000

; There should be no further modification needed
org NUKE_VIRTUAL_ADDRESS

header_multiboot:
MB_MAGIC equ 0x1BADB002
MB_FLAGS equ 0x00000107
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

magic dd MB_MAGIC
flags dd MB_FLAGS
checksum dd MB_CHECKSUM

addr_header dd NUKE_VIRTUAL_ADDRESS
addr_load dd NUKE_VIRTUAL_ADDRESS
addr_load_end dd NUKE_END
addr_bss_end dd NUKE_END
entry_addr dd NUKE_ENTRY

times 0x20-($-$$) db 0xFF

NUKE_ENTRY:

[bits 32]
incbin "bin/loader"

jmp NUKE_KERNEL_ENTRY
times 0x1000-($-$$) db 0x90
NUKE_KERNEL_ENTRY:

incbin "bin/kernel"

[bits 64]
loop:
hlt
jmp loop

NUKE_END:
