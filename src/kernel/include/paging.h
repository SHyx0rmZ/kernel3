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

#ifndef _PAGING_H_
#define _PAGING_H_

#include "types.h"
/*
 * Variables
 */

#define PAGING_P 		0x01
#define PAGING_W 		0x02
#define PAGING_U 		0x04
#define PAGING_PWT 		0x08
#define PAGING_PCD 		0x10
#define PAGING_A 		0x20
#define PAGING_NX 		0x8000000000000000LL

#define PDE_D 			0x0040
#define PDE_1 			0x0080
#define PDE_G 			0x0100
#define PDE_PAT 		0x1000

#define PML4E_BASE_ADDRESS 	0x000FFFFFFFFFF000LL
#define PDPE_BASE_ADDRESS 	0x000FFFFFFFFFF000LL
#define PDE_BASE_ADDRESS	0x000FFFFFFFE00000LL

/*
 * Structs
 */

typedef qword pml4e_t;
typedef qword pdpe_t;
typedef qword pde_t;

/*
 * Functions
 */

bool paging_map(qword address_physical, qword address_virtual, byte pages);

#endif
