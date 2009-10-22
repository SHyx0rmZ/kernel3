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
#include "util.h"
//#include "idt.h"

struct multiboot_info_t multiboot_info;

void ewrin()
{
	print_set(66);
	print("[", COLOR_GRAY);
	print("EPIC WRIN", COLOR_GREEN);
	print("]\r\n", COLOR_GRAY);
}

void efail()
{
	print_set(66);
	print("[", COLOR_GRAY);
	print("EPIC FAIL", COLOR_RED);
	print("]\r\n", COLOR_GRAY);
}

void kernel(long magic, multiboot_info_t *multiboot_info_pointer)
{
	if(magic != 0x2BADB002)
	{
		print("Multiboot isn't magic", COLOR_RED);
		reboot();
	}

	memcpy(&multiboot_info, multiboot_info_pointer, sizeof(struct multiboot_info_t));

	if((multiboot_info.flags & 0x40) == 0)
	{
		print("Can't get memory map", COLOR_RED);
		reboot();
	}

	print("ASXSoft ", COLOR_GRAY);
	print("Nuke\r\nXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX", COLOR_BLUE);

	if(inb(0x03CC) == 0)	
	{
		byte old = inb(0x03B4);
		outb(0x03B4, 0x0A);
		outb(0x03B5, 0x3F);
		outb(0x03B4, old);
	}
	else
	{
		byte old = inb(0x03D4);
		outb(0x03D4, 0x0A);
		outb(0x03D5, 0x3F);
		outb(0x03D4, old);
	}

	print("Setting up GDT...", COLOR_GRAY);

	gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(2, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	gdt_set_entry(3, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	gdt_set_entry(4, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_3 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	
	gdt_load();

	gdt_flush_registers(0x08, 0x10, 0x10, 0x00, 0x00, 0x10);

	ewrin();

	print("Switching to ", COLOR_GRAY);
	print("Long Mode", COLOR_YELLOW);
	print("...", COLOR_GRAY);

	ewrin();

	while(1) { asm("hlt"); };
}
