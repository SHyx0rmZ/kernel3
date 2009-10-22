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

#ifndef _MULTIBOOT_H_ 
#define _MULTIBOOT_H_

#include "types.h"

typedef struct multiboot_info_t {
	dword flags;
	dword mem_lower;
	dword mem_upper;
	dword boot_device;
	dword cmdline;
	dword mods_count;
	dword mods_addr;
	dword tabsize_or_num;
	dword strsize_or_size;
	dword addr_or_addr;
	dword reserver_or_shndx;
	dword mmap_length;
	dword mmap_addr;
	dword drives_length;
	dword drives_addr;
	dword config_table;
	dword boot_loader_name;
	dword apm_table;
	dword vbe_control_info;
	dword vbe_mode_info;
	dword vbe_mode;
	dword vbe_interface_seg;
	dword vbe_interface_off;
	dword vbe_interface_len;
} multiboot_info_t;

#endif
