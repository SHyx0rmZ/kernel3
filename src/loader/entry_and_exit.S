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

times 256 db 00

NUKE_LOADER_END_STACK:

section .module_exit
NUKE_LOADER_EXIT:
pop edi
pop esi
jmp 0x100FE0
