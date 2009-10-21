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

#include "reboot.h"
#include "print.h"

void reboot()
{
	print("!\r\nPress any key to reboot...", COLOR_GRAY);

	asm(
		// Auf Tastendruck warten
		"wait0: \n"
		"inb $0x64, %al \n"
		"test $0x01, %al \n"
		"jz wait0 \n"
		"inb $0x60, %al \n"		
		// Warten bis Eingabepuffer leer ist
		"wait1: \n"
		"inb $0x64, %al \n"
		"test $0x02, %al \n"
		"jne wait1 \n"
 		// Befehl 0xD1 zum schreiben des Inputports an den KBC senden
		"mov $0xD1, %al \n"
		"outb  %al, $0x64 \n"
 		// Wieder warten bis der Eingabepuffer leer ist
		"wait2: \n"
		"inb $0x64, %al \n"
		"test $0x02, %al \n"
		"jne  wait2 \n"
		// Den neuen Wert für den Inputport über Port 0x60 senden
		"mov $0xFE, %al \n"
		"outb %al, $0x60 \n"
	);

}
