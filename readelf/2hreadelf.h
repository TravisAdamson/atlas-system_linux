#ifndef __2HREADELF_H__
#define __2HREADELF_H__

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <byteswap.h>
#include <string.h>

void print_program_headers_64(Elf64_Ehdr *ehdr,
							Elf64_Phdr *phdr,
							Elf64_Shdr *shdr,
							const char *maps,
							int is_big_endian);

void print_program_headers_32(Elf32_Ehdr *ehdr32,
							  Elf32_Phdr *phdr32,
							  Elf32_Shdr *shdr32,
							  const char *maps,
							  int is_big_endian);

void swap_endianess_64(Elf64_Phdr *phdr, int phnum);

void swap_endianess_32(Elf32_Ehdr *ehdr,
					Elf32_Phdr *phdr,
					Elf32_Shdr *shdr,
					int phnum);

const char *get_file_type(uint16_t e_type);

const char *get_segment_type(uint32_t p_type);

#endif
