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

int print_32(Elf32_Ehdr * ehdr, Elf32_Shdr * shdr, const char *maps,
					 int is_big_endian);

int print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps);

int setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr *ehdr,
					const char *maps);

char get_type_32(Elf32_Sym s_table, Elf32_Shdr *shdr);

char get_type_64(Elf64_Sym s_table, Elf64_Shdr *shdr);

void print_tables_32(int num_symbols, Elf32_Sym *s_table,
					 char *strtab, Elf32_Shdr *shdr);

void print_tables_64(int num_symbols, Elf64_Sym *s_table,
					 char *strtab, Elf64_Shdr *shdr);

void swap_endianess(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, int shnum);

#endif
