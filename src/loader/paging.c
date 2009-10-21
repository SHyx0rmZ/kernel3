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
#include "paging.h"

qword *paging_initialize()
{
	qword *pml4e = (qword *)0x6000LL;
	*pml4e = 0x700BLL;
	qword *pdpe = (qword *)0x7000LL;
	*pdpe = 0x800BLL;
	qword *pd1 = (qword *)0x8000LL;
	qword *pd2 = (qword *)0x8008LL;
	qword *pd3 = (qword *)0x8010LL;
	qword *pd4 = (qword *)0x8018LL;
	qword *pd5 = (qword *)0x8020LL;
	qword *pd6 = (qword *)0x8028LL;
	qword *pd7 = (qword *)0x8030LL;
	qword *pd8 = (qword *)0x8038LL;
	
	*pd1 = 0x00018FLL;
	*pd2 = 0x20018FLL;
	*pd3 = 0x40018FLL;
	*pd4 = 0x60018FLL;
	*pd5 = 0x80018FLL;
	*pd6 = 0xA0018FLL;
	*pd7 = 0xC0018FLL;
	*pd8 = 0xE0018FLL;

	return (qword *)0x6000LL;
}

void paging_activate(qword *pml4)
{
	asm(
		"push %%eax \n"
		"push %%ecx \n"

		"mov %%cr4, %%eax \n"
		"or $0xA0, %%eax \n"
		"mov %%eax, %%cr4 \n"

		"mov %0, %%eax \n"
		"mov %%cr3, %%eax \n"

		"mov $0xC0000080, %%ecx \n"
		"rdmsr \n"
		"or $0x0100, %%eax \n"
		"wrmsr \n"

		"mov %%cr0, %%eax \n"
		"or $0x80000000, %%eax \n"
		"mov %%eax, %%cr0 \n"
		
		"pop %%ecx \n"
		"pop %%eax \n"
		:
		: "g"(pml4)
	   );
}
