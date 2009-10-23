/*
 *   ASXSoft Nuke - Operating System
 *   Copyright (C) 2009  Patrick Pokatilo
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _IDT_H_
#define _IDT_H_

#include "types.h"

/*
 * Variables
 */

#define IDT_PRESENT		0x80
#define IDT_RING_3		0x60
#define IDT_RING_2		0x40
#define IDT_RING_1		0x20
#define IDT_RING_0		0x00
#define IDT_TRAP_GATE		0x0F
#define IDT_INTERRUPT_GATE	0x0E
#define IDT_CALL_GATE		0x0C

#define IRQ_BASE		0x20

/*
 * Structs
 */

// idt_entry_t
typedef struct
{
	word offset_low;
	word selector;
	byte ist;
	byte flags;
	word offset_middle;
	dword offset_high;
	dword reserved;
} idt_entry_t;

// idt_pointer_t
typedef struct
{
	word limit;
	qword base;
} __attribute__ ((packed))
idt_pointer_t;

/*
 * Functions
 */

void idt_set_entry(word index, word selector, void *offset, byte flags, byte ist);
void idt_initialize();
void idt_load();

#endif
