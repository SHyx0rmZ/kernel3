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
#include "idt.h"
#include "int.h"

extern void null_handler();

extern void exception_stub_0();
extern void exception_stub_1();
extern void exception_stub_2();
extern void exception_stub_3();
extern void exception_stub_4();
extern void exception_stub_5();
extern void exception_stub_6();
extern void exception_stub_7();
extern void exception_stub_8();
extern void exception_stub_9();
extern void exception_stub_10();
extern void exception_stub_11();
extern void exception_stub_12();
extern void exception_stub_13();
extern void exception_stub_14();
extern void exception_stub_16();
extern void exception_stub_17();
extern void exception_stub_18();
extern void exception_stub_19();

extern void irq_stub_0();
extern void irq_stub_1();
extern void irq_stub_2();
extern void irq_stub_3();
extern void irq_stub_4();
extern void irq_stub_5();
extern void irq_stub_6();
extern void irq_stub_7();
extern void irq_stub_8();
extern void irq_stub_9();
extern void irq_stub_10();
extern void irq_stub_11();
extern void irq_stub_12();
extern void irq_stub_13();
extern void irq_stub_14();
extern void irq_stub_15();


idt_entry_t idt[256];
idt_pointer_t idt_pointer;

void idt_load()
{
	idt_pointer.limit = (word)(256 * 16 - 1);
	idt_pointer.base = (qword)idt;

	asm("lidt %0" : : "g" (idt_pointer));
}

void idt_set_entry(word index, word selector, void *offset, byte flags, byte ist)
{
	idt[index].offset_low = (word)((qword)offset & 0xFFFF);
	idt[index].selector = selector;
	idt[index].ist = ist;
	idt[index].flags = flags;
	idt[index].offset_middle = (word)(((qword)offset >> 16) & 0xFFFF);
	idt[index].offset_high = (dword)(((qword)offset >> 32) & 0xFFFFFFFF);
	idt[index].reserved = 0;
}

void idt_initialize()
{
	word i;

	for (i = 0; i < 256; i++)
	{
		idt_set_entry(i, 0x08, &null_handler, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	}


	idt_set_entry(0, 0x08, exception_stub_0, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(1, 0x08, exception_stub_1, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(2, 0x08, exception_stub_2, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(3, 0x08, exception_stub_3, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(4, 0x08, exception_stub_4, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(5, 0x08, exception_stub_5, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(6, 0x08, exception_stub_6, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(7, 0x08, exception_stub_7, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(8, 0x08, exception_stub_8, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(9, 0x08, exception_stub_9, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(10, 0x08, exception_stub_10, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(11, 0x08, exception_stub_11, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(12, 0x08, exception_stub_12, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(13, 0x08, exception_stub_13, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(14, 0x08, exception_stub_14, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(16, 0x08, exception_stub_16, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(17, 0x08, exception_stub_17, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(18, 0x08, exception_stub_18, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(19, 0x08, exception_stub_19, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);

	idt_set_entry(IRQ_BASE + 0, 0x08, irq_stub_0, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 1, 0x08, irq_stub_1, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 2, 0x08, irq_stub_2, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 3, 0x08, irq_stub_3, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 4, 0x08, irq_stub_4, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 5, 0x08, irq_stub_5, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 6, 0x08, irq_stub_6, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 7, 0x08, irq_stub_7, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 8, 0x08, irq_stub_8, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 9, 0x08, irq_stub_9, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 10, 0x08, irq_stub_10, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 11, 0x08, irq_stub_11, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 12, 0x08, irq_stub_12, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 13, 0x08, irq_stub_13, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 14, 0x08, irq_stub_14, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);
	idt_set_entry(IRQ_BASE + 15, 0x08, irq_stub_15, IDT_PRESENT | IDT_RING_0 | IDT_INTERRUPT_GATE, 0);

	irq_initialize();
}
