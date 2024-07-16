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

void print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					 int is_big_endian);

void print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps,
					 int is_big_endian);

void setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr *ehdr,
					const char *maps);

char get_type_32(Elf32_Sym s_table);

void print_tables_32(int num_symbols, Elf32_Sym *s_table,
					 int is_big_endian, char *strtab,
					 Elf32_Shdr *shdr);

void swap_endianess_32(Elf32_Shdr *shdr, int shnum);

void swap_endianess(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, int shnum);

#endif
