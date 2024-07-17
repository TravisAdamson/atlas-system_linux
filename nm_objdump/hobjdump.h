#ifndef __HNM_H__
#define __HNM_H__

#include "elfmacros.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <byteswap.h>
#include <string.h>

int setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr *ehdr,
					const char *maps);

int print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					int is_big_endian);

int print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps);

void swap_endianess(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, int shnum);

void print_section(const char *section, int size, int address);

void print_hex_ascii_line(const char *data, int len, int offset);

#endif
