;   ASXSoft Nuke - Operating System
;   Copyright (C) 2009  Patrick Pokatilo
;
;   This program is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.
;
;   This program is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.
;
;   You should have received a copy of the GNU General Public License
;   along with this program.  If not, see <http://www.gnu.org/licenses/>.

NUKE_VIRTUAL_ADDRESS equ 0x100000

; There should be no further modification needed
org NUKE_VIRTUAL_ADDRESS

header_multiboot:
MB_MAGIC equ 0x1BADB002
MB_FLAGS equ 0x00010003
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

times 0x0FE0-($-$$) db 0x90
push 0x18
jmp NUKE_KERNEL_ENTRY
times 0x1000-($-$$) db 0x90
NUKE_KERNEL_ENTRY:

incbin "bin/kernel"

[bits 64]
loop:
hlt
jmp loop

NUKE_END:
