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

int setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr * ehdr,
					const char *maps, const char *filename);

void print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const unsigned char *maps,
					int is_big_endian, const char *filename);

void print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const unsigned char *maps,
			 const char *filename);

void swap_endianess(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, int shnum);

void print_section_contents_64(Elf64_Shdr *section,
							const unsigned char *section_name,
							const unsigned char *maps);

void print_section_contents_32(Elf32_Shdr *section,
							const unsigned char *section_name,
							const unsigned char *maps);

void print_header_32(Elf32_Ehdr *ehdr, const char *filename);

#endif
