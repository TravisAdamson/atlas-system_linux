#ifndef __1READELF_H__
#define __1READELF_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <elf.h>
#include <byteswap.h>

void print_section_headers_32(Elf32_Ehdr * ehdr,
							  Elf32_Shdr * shdr,
							  const char *strtab);
void print_section_headers_64(Elf64_Ehdr *ehdr,
							  Elf64_Shdr *shdr,
							  const char *strtab);
void *open_and_map_file(const char *filename, size_t *filesize);
void check_elf_magic(Elf64_Ehdr *ehdr);
void process_elf(void *maps, size_t filesize);
void process_elf64(Elf64_Ehdr *ehdr, int is_big_endian, void *maps);
void process_elf32(Elf32_Ehdr *ehdr32, int is_big_endian, void *maps);
void swap_endianess_64(Elf64_Shdr *shdr, int shnum);
void swap_endianess_32(Elf32_Shdr *shdr, int shnum);
void print_flag_key(void);
const char *flags_to_string(uint64_t flags);
const char *get_section_type_name_64(uint32_t sh_type);
const char *get_section_type_name_32(uint32_t sh_type);

#endif
