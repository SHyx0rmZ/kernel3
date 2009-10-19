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
#include "print.h"

byte *videomemory = (byte *)0xB8000;

void clear_screen()
{
	word *video;

	for(video = (word *)0xB8000; video < (word *)0xB8FA0; video++)
	{
		*video = 0x0720;
	}

	videomemory = (byte *)0xB8000;
}

void print(const char *text, byte flags)
{
	byte *c;

	for(c = (byte *)&text[0]; *c != 0; c++)
	{
		while(videomemory < (byte *)0xB8000)
		{
			videomemory += 0xA0;
		}

		if(*c == '\n')
		{
			videomemory += 0xA0;
		}

		if(*c == '\r')
		{
			videomemory = (byte *)(videomemory - ((dword)(videomemory - 0xB8000) % 0xA0));
		}

		while(videomemory > (byte *)0xB8FA0)
		{
			byte *videosrc = (byte *)0xB80A0;
			byte *videodest = (byte *)0xB8000;

			while(videosrc < (byte *)0xB8FA0)
			{
				*videodest++ = *videosrc++;
			}

			videomemory -= 0xA0;
		}
		
		if(*c != '\r' && *c != '\n')
		{
			*videomemory++ = *c;
			*videomemory++ = flags; 
		}
	}
}
