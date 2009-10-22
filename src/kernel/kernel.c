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

#include "types.h"
#include "print.h"
#include "multiboot.h"
#include "reboot.h"
#include "gdt.h"
//#include "idt.h"

void kernel(long magic, multiboot_info_t *multiboot)
{
	if(magic != 0x2BADB002)
	{
		print("Multiboot isn't magic", COLOR_RED);
		reboot();
	}

	if((multiboot->flags & 0x40) == 0)
	{
		print("Can't get memory map", COLOR_RED);
		reboot();
	}

	dword i = 0;

	for(i = 1; i < 0x80000000; i = i << 1)
	{
		if((multiboot->flags & i) != 0)
			print("Set ", COLOR_GREEN);
		else
			print("Cleared ", COLOR_RED);
	}

	print("ASXSoft ", COLOR_GRAY);
	print("Nuke\r\n", COLOR_BLUE);

	print("Successfully ", COLOR_GREEN);
	print("switched to ", COLOR_GRAY);
	print("Long Mode\r\n", COLOR_YELLOW);

	print("Setting up GDT...                                            ", COLOR_GRAY);

	gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(2, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	gdt_set_entry(3, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(4, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	
	gdt_load();

	gdt_flush_registers(0x08, 0x10, 0x10, 0x00, 0x00, 0x10);

	print("OK", COLOR_GREEN);

	while(1) { asm("hlt"); };
}
