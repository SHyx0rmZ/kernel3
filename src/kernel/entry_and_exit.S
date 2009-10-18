extern kernel

[bits 32]
section .module_entry
NUKE_KERNEL_ENTRY:

sub esp, 4
mov [esp], dword kernel
retf

section .module_exit
NUKE_KERNEL_EXIT:
