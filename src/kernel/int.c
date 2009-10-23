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
#include "int.h"
#include "util.h"
#include "print.h"

void handle_interrupt(cpu_state_t *cpu_state)
{
	if(cpu_state->interrupt <= 0x19)
	{
	}
	else if(cpu_state->interrupt >= IRQ_BASE && cpu_state->interrupt <= (IRQ_BASE + 15))
	{
		if(cpu_state->interrupt >= (IRQ_BASE +  8))
		{
			outb(PIC2, PIC_EOI);
		}

		outb(PIC1, PIC_EOI);
	}
	else
	{
		print("Invalid interrupt!", COLOR_RED);
	}
}

void irq_initialize()
{
	outb(PIC1_COMMAND, ICW1_INIT + ICW1_ICW4);
	outb(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);

	outb(PIC1_DATA, IRQ_BASE);
	outb(PIC2_DATA, IRQ_BASE + 8);
	
	outb(PIC1_DATA, 4);
	outb(PIC2_DATA, 2);

	outb(PIC1_DATA, ICW4_8086);
	outb(PIC2_DATA, ICW4_8086);

	outb(PIC1_DATA, 0x00);
	outb(PIC2_DATA, 0x00);

	asm("sti");
}
