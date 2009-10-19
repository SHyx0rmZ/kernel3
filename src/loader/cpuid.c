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
#include "cpuid.h"

bool initialized = FALSE, supported = FALSE;
dword standard = 0x00000000, extended = 0x80000000;

void cpuid_check_support()
{
	asm(
		"push %%eax \n"
		"push %%ecx \n"
		"pushf \n"
		"pushf \n"
		"pop %%eax \n"
		"mov %%eax, %%ecx \n"
		"xor $0x200000, %%eax \n"
		"push %%eax \n"
		"popf \n"
		"pushf \n"
		"pop %%eax \n"
		"xor %%ecx, %%eax"
		: "=a" (supported)
	   );

	asm(
		"pop %ecx \n"
		"pop %eax \n"
	   );

	if(supported)
	{
		standard = cpuid(0x00000000)->eax;
		extended = cpuid(0x80000000)->eax;
	}
}

cpuid_result_t *cpuid_standard(dword function)
{
	return cpuid(function);
}

cpuid_result_t *cpuid_extended(dword function)
{
	if(function < 0x80000000)
	{
		function += 0x80000000;
	}

	return cpuid(function);
}

cpuid_result_t *cpuid(dword function)
{
	cpuid_result_t *result;
	
	if(function != 0x00000000 && function != 0x80000000)
	{
		if(initialized == FALSE)
		{
			cpuid_check_support();

			initialized = TRUE;
		}

		if(function < 0x80000000)
		{
			if(function > standard)
			{
				return NULL;
			}
		}
		else
		{
			if(function > extended)
			{
				return NULL;
			}
		}
	}

	asm(
		"push %eax \n"
		"push %ebx \n"
		"push %ecx \n"
		"push %edx \n"
	   );

	asm(
		"cpuid \n"
		: "=a" (result->eax), "=b" (result->ebx), "=c" (result->ecx), "=d" (result->edx)
		: "a" (function)
	   );

	asm(
		"pop %edx \n"
		"pop %ecx \n"
		"pop %ebx \n"
		"pop %eax \n"
	   );

	return result;
}
