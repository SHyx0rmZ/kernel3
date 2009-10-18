#   ASXSoft Nuke - Operating System
#   Copyright (C) 2009  Patrick Pokatilo
#
#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

SRCS_LOADER = $(shell find src/loader -name '*.c') src/loader/entry_and_exit.S
SRCS_KERNEL = $(shell find src/kernel -name '*.c') src/loader/entry_and_exit.S

OBJS_LOADER = $(addprefix obj/loader/,$(notdir $(addsuffix .o,$(basename $(SRCS_LOADER)))))
OBJS_KERNEL = $(addprefix obj/kernel/,$(notdir $(addsuffix .o,$(basename $(SRCS_KERNEL)))))

CC = gcc
LD = ld
AS = nasm

M32 = -m32
M64 = -m64

CCFLAGS = -c -Wall -Wextra -Werror -fno-stack-protector -fno-builtin -nostdlib -nodefaultlibs -fverbose-asm
LDFLAGS = -O3 -s

bin/nuke.nke: bin/loader bin/kernel src/nuke.asm src/loader/loader.ld src/kernel/kernel.ld
	@echo " [AS] $@"
	@$(AS) -f bin -o $@ src/nuke.asm

bin/loader: $(OBJS_LOADER)
	@echo " [LD] $@"
	@$(LD) -Tsrc/loader/loader.ld $(OBJS_LOADER) -o $@

bin/kernel: $(OBJS_KERNEL)
	@echo " [LD] $@"
	@$(LD) -Tsrc/kernel/kernel.ld $(OBJS_KERNEL) -o $@

obj/loader/%.o: $(addprefix src/loader/,$(notdir %.c))
	@echo " [CC 32] $^"
	@$(CC) $(CCFLAGS) $(M32) -Isrc/loader/include -o $@ $^

obj/kernel/%.o: $(addprefix src/kernel/,$(notdir %.c))
	@echo " [CC 64] $^"
	@$(CC) $(CCFLAGS) $(M64) -Isrc/kernel/include -o $@ $^

obj/loader/%.o: $(addprefix src/loader/,$(notdir %.S))
	@echo " [AS 32] $^"
	@$(AS) -f elf32 -o $@ $^

obj/kernel/%.o: $(addprefix src/kernel/,$(notdir %.S))
	@echo " [AS 64] $^"
	@$(AS) -f elf64 -o $@ $^

clean:
	@echo " [RM] $(OBJS_LOADER) $(OBJS_KERNEL)"
	@rm $(OBJS_LOADER) $(OBJS_KERNEL)

.PHONY: clean
