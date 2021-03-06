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
#include "gdt.h"
#include "cpuid.h"
#include "print.h"
#include "reboot.h"
#include "paging.h"

void loader()
{
	clear_screen();

	gdt_set_entry(0, 0, 0, 0, 0);
	gdt_set_entry(1, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_PROTECTED_MODE);
	gdt_set_entry(2, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_WRITABLE | GDT_DIRECTION_UP, GDT_GRANULAR | GDT_PROTECTED_MODE);
	gdt_set_entry(3, 0, GDT_LIMIT, GDT_PRESENT | GDT_RING_0 | GDT_SEGMENT | GDT_EXECUTABLE | GDT_READABLE, GDT_GRANULAR | GDT_LONG_MODE);
	
	gdt_load();

	gdt_flush_registers(0x08, 0x10, 0x10, 0x00, 0x00, 0x10);

	cpuid_result_t *cpuid;

	cpuid = cpuid_extended(0x80000001);
	
	if((cpuid->edx & 0x20000000) == NULL)
	{
		print("Your CPU does not support Long Mode", COLOR_RED);
		reboot();
	}

	cpuid = cpuid_standard(0x00000001);

	if((cpuid->edx & 0x40) == NULL)
	{
		print("Your CPU doe not support Physical Adress Extension", COLOR_RED);
		reboot();
	}

	qword *pml4 = paging_initialize();
	
	paging_activate(pml4);

	//asm(
	//	"push $0x18 \n"
	//   );
}
