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

#ifndef _GDT_H_
#define _GDT_H_

#include "types.h"

/*
 * Variables
 */

#define GDT_LIMIT			0xFFFFFFFF

// Access
#define GDT_PRESENT	 		0x80
#define GDT_RING_3			0x60
#define GDT_RING_2			0x40
#define GDT_RING_1			0x20
#define GDT_RING_0			0x00
#define GDT_SEGMENT			0x10
#define GDT_EXECUTABLE			0x08
#define GDT_DIRECTION_DOWN		0x04
#define GDT_DIRECTION_UP		0x00
#define GDT_CONFORMING			0x04
#define GDT_READABLE			0x02
#define GDT_WRITABLE			0x02
#define GDT_ACCESSED			0x01

// Flags
#define GDT_GRANULAR	 		0x08
#define GDT_PROTECTED_MODE		0x04
#define GDT_REAL_MODE			0x00
#define GDT_LONG_MODE	 		0x02
#define GDT_AVAILABLE	 		0x01

/*
 * Structs
 */

// gdt_entry_t
typedef struct
{
	word limit_low;
	word base_low;
	byte base_middle;
	byte access;
	byte flags_and_limit_high;
	byte base_high;
} 
__attribute__((packed)) 
gdt_entry_t;

// gdt_pointer_t
typedef struct
{
	word limit;
	dword base;
} 
__attribute__((packed)) 
gdt_pointer_t;

/*
 * Functions
 */

void gdt_flush_registers(word cs, word ds, word es, word fs, word gs, word ss);
void gdt_load();
void gdt_load_limited(word entries);
void gdt_set_entry(word index, dword base, dword limit, byte access, byte flags);

#endif
