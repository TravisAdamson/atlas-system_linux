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

void print_section_headers_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *strtab);
void print_section_headers_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *strtab);

#endif
