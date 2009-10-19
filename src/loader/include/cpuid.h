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

#ifndef _CPUID_H_
#define _CPUID_H_

#include "types.h"

/*
 * Structs
 */

typedef struct
{
	dword eax;
	dword ebx;
	dword ecx;
	dword edx;
}
cpuid_result_t;

/*
 * Functions
 */

void cpuid_check_support(); // Doesn't need to be called explicitly
cpuid_result_t *cpuid_standard(dword number);
cpuid_result_t *cpuid_extended(dword number);
cpuid_result_t *cpuid(dword number);

#endif
