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

gdt_entry_t gdt[4];
gdt_pointer_t gdt_pointer;

void gdt_flush_registers(word cs, word ds, word es, word fs, word gs, word ss)
{
	asm(
		"push %0 \n"
		"push $farjump \n"
		"retf \n"
		"farjump: \n"
		"mov %1, %%ds \n"
		"mov %2, %%es \n"
		"mov %3, %%fs \n"
		"mov %4, %%gs \n"
		"mov %5, %%ss \n"
		:
		: "g" (cs), "g" (ds), "g" (es), "g" (fs), "g" (gs), "g" (ss)
		: "eax"
	);
}

void gdt_load()
{
	gdt_pointer.limit = (word)(4 * 8 - 1);
	gdt_pointer.base = (dword)gdt;

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
}
