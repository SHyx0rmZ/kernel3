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

section .text

%define IRQ_BASE 0x20

extern handle_interrupt

%macro exception_stub 1
global exception_stub_%1
exception_stub_%1:
	push qword 0
	push qword %1
	jmp int_common
%endmacro

%macro exception_stub_error_code 1
global exception_stub_%1
exception_stub_%1:
	push qword %1
	jmp int_common
%endmacro

%macro irq_stub 1
global irq_stub_%1
irq_stub_%1:
	push qword 0
	push qword %1 + IRQ_BASE
	jmp int_common
%endmacro

global null_handler
null_handler:
	push qword 0
	push qword 0xc0de
	jmp int_common

exception_stub 0
exception_stub 1
exception_stub 2
exception_stub 3
exception_stub 4
exception_stub 5
exception_stub 6
exception_stub 7
exception_stub_error_code 8
exception_stub 9
exception_stub_error_code 10
exception_stub_error_code 11
exception_stub_error_code 12
exception_stub_error_code 13
exception_stub_error_code 14
exception_stub 16
exception_stub_error_code 17
exception_stub 18
exception_stub 19

irq_stub 0
irq_stub 1
irq_stub 2
irq_stub 3
irq_stub 4
irq_stub 5
irq_stub 6
irq_stub 7
irq_stub 8
irq_stub 9
irq_stub 10
irq_stub 11
irq_stub 12
irq_stub 13
irq_stub 14
irq_stub 15

int_common:
	push r15
	push r14
	push r13
	push r12
	push r11
	push r10
	push r9
	push r8
	push rbp
	push rdi
	push rsi
	push rdx
	push rcx
	push rbx
	push rax
	
	mov rdi, rsp
	call handle_interrupt

	pop rax
	pop rbx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	pop rbp
	pop r8
	pop r9
	pop r10
	pop r11
	pop r12
	pop r13
	pop r14
	pop r15

	add rsp, 0x10

	iretq
