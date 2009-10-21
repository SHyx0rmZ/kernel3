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

void kernel(int magic, multiboot_info_t *multiboot)
{
	if(magic != 0x2BADB002)
	{
		print("Multiboot isn't magic", COLOR_RED);
		reboot();
	}

	magic = multiboot->flags;



	print("Booted into Long Mode, horray!\n", COLOR_GREEN);
	print("Does this really work?", COLOR_GRAY);

	while(1) { asm("hlt"); };
}
