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
#include "util.h"

void *memcpy(void *destination, const void *source, qword count)
{
	const byte *sp = (const byte*)source;
	byte *dp = (byte*)destination;

	for(;count != 0; count--)
	{
		*(dp++) = *(sp++);
	}

	return destination;	
}

void *memset(void *destination, byte value, qword count)
{
	byte *dp = (byte*)destination;
	
	for(; count != 0; count--)
	{
		*(dp++) = (byte)value;
	}

	return destination;
}

byte inb(word port)
{
	byte data;

	asm(
		"mov %1, %%dx \n"
		"inb %%dx, %%al \n"
		"mov %%al, %0 \n"
		: "=g" (data)
		: "g" (port)
		: "rax", "rdx"
	   );

	return data;
}

void outb(word port, byte data)
{
	asm(
		"mov %0, %%dx \n"
		"mov %1, %%al \n"
		"outb %%al, %%dx \n"
		:
		: "g" (port), "g" (data)
		: "rax", "rdx"
	   );
}

word inw(word port)
{
	word data;

	asm(
		"mov %1, %%dx \n"
		"inw %%dx, %%ax \n"
		"mov %%ax, %0 \n"
		: "=g" (data)
		: "g" (port)
		: "rax", "rdx"
	   );

	return data;
}

void outw(word port, word data)
{
	asm(
		"mov %0, %%dx \n"
		"mov %1, %%ax \n"
		"outw %%ax, %%dx \n"
		:
		: "g" (port), "g" (data)
		: "rax", "rdx"
	   );
}

dword ind(word port)
{
	dword data;

	asm(
		"mov %1, %%dx \n"
		"inl %%dx, %%eax \n"
		"mov %%eax, %0 \n"
		: "=g" (data)
		: "g" (port)
		: "rax", "rdx"
	   );

	return data;
}

void outd(word port, dword data)
{
	asm(
		"mov %0, %%dx \n"
		"mov %1, %%eax \n"
		"outl %%eax, %%dx \n"
		:
		: "g" (port), "g" (data)
		: "rax", "rdx"
	   );
}
