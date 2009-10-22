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

#include "gdt.h"

gdt_entry_t gdt[256];
gdt_pointer_t gdt_pointer;
word gdt_entries = 0;

void gdt_flush_registers(word cs, word ds, word es, word fs, word gs, word ss)
{
	asm(
		"xor %%rax, %%rax \n"
		"mov %0, %%ax \n"
		"pop %%rbx \n"
		"pop %%rcx \n"
		"push %%rax \n"
		"push $1f \n"
		"rex.w retf \n"
		"nop \n"
		"1: \n"
		"push %%rcx \n"
		"push %%rbx \n"
		"mov %1, %%ds \n"
		"mov %2, %%es \n"
		"mov %3, %%fs \n"
		"mov %4, %%gs \n"
		"mov %5, %%ss \n"
		:
		: "g" (cs), "g" (ds), "g" (es), "g" (fs), "g" (gs), "g" (ss)
		: "rax", "rbx", "rcx"
	);
}

void gdt_load()
{
	gdt_pointer.limit = (word)(gdt_entries * 8 - 1);
	gdt_pointer.base = (qword)gdt;

	asm("lgdt %0" : : "m" (gdt_pointer));
}

void gdt_set_entry(word index, dword base, dword limit, byte access, byte flags)
{
	gdt[index].limit_low = limit & 0xFFFF;
	gdt[index].flags_and_limit_high = (flags << 4) | ((limit >> 16) & 0x0F);
	gdt[index].base_low = base & 0xFFFF;
	gdt[index].base_middle = (base >> 16) & 0xFF;
	gdt[index].base_high = (base >> 24) & 0xFF;
	gdt[index].access = access;

	if(++index > gdt_entries)
	{
		gdt_entries = index;
	}
}

void gdt_initialize()
{
	gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(2, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	gdt_set_entry(3, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(4, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
}
