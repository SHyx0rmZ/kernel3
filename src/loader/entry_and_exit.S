[bits 32]
extern loader

section .module_entry
NUKE_LOADER_ENTRY:
cli
mov esp, NUKE_LOADER_END_STACK
push ebx
push eax

call loader
jmp NUKE_LOADER_EXIT

NUKE_LOADER_START_STACK:

times 64 db 00

NUKE_LOADER_END_STACK:

section .module_exit
NUKE_LOADER_EXIT:
