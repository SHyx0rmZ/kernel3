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

pml4e_t *pagemap[512];

bool paging_map(qword address_physical, qword address_virtual, byte pages)
{
	address_physical += 1;
	address_virtual += 1;
	pages += 1;
	/*//TODO: OMGWTFBBQ, 64-Bit pointers in 32-Bit?!?
	pml4e_t *pml4e;
	pdpe_t *pdpe;
	pde_t *pde;

	byte i;

	for(i = 0; i < pages; i++)
	{
		dword pml4_index = (address_virtual >> 39) & 0x01FF;
		dword pdp_index = (address_virtual >> 30) & 0x01FF;
		dword pd_index = (address_virtual >> 21) & 0x01FF;

		pml4e = pagemap[pml4_index];
		
		if((pml4e & PAGING_P) == 0)
		{
			*pml4e = (pml4e_t)((qword)address_free & PML4E_BASE_ADDRESS) | PAGING_PWT | PAGING_U | PAGING_W | PAGING_P;
		}

		pdpe = (pdpe_t *)((qword)*pml4e & PML4E_BASE_ADDRESS);

		if((pdpe & PAGING_P) == 0)
		{
			*pdpe = (address_free & PDPE_BASE_ADDRESS) | PAGING_PWT | PAGING_U | PAGING_W | PAGING_P;
		}
		
		pde = (pde_t *)(*pdpe & PDPE_BASE_ADDRESS);

		if((pde & PAGING_P) != 0)
		{
			//TODO: Page swapping
			return FALSE;
		}

		*pde = (address_physical & PDE_BASE_ADDRESS) | PDE_1 | PAGING_PWT | PAGING_W | PAGING_P;

	}*/

	return TRUE;
}
