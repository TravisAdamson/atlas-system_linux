#ifndef __readelf_h__
#define __readelf_h__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define LE "2's complement, little endian"
#define BE "2's complement, big endian"
#define UNKOWN53 83

void print_head_32(Elf32_Ehdr *e_hdr);
void print_head_64(Elf64_Ehdr *e_hdr);
void print_osabi_64(Elf64_Ehdr *e_hdr);
void print_machine_64(Elf64_Ehdr *e_hdr);
void print_machine_64_2(Elf64_Ehdr *e_hdr);
void print_machine_32(Elf32_Ehdr *e_hdr);
void print_machine_32_2(unsigned int new_ident);
void print_osabi_32(Elf32_Ehdr *e_hdr);
void print_type_32(Elf32_Ehdr *e_hdr);
void print_type_64(Elf64_Ehdr *e_hdr);
void print_offset_32(Elf32_Ehdr *e_hdr);
void print_offset_64(Elf64_Ehdr *e_hdr);
void print_poffset_64(Elf64_Ehdr *e_hdr);
void print_poffset_32(Elf32_Ehdr *e_hdr);
void print_header_size_32(Elf32_Ehdr *e_hdr);
void print_pheader_size_32(Elf32_Ehdr *e_hdr);
void print_sheader_size_32(Elf32_Ehdr *e_hdr);
void print_ver_32(Elf32_Ehdr *e_hdr);
void print_entry_32(Elf32_Ehdr *e_hdr);
void print_nprog_head_32(Elf32_Ehdr *e_hdr);
void print_nsys_head_32(Elf32_Ehdr *e_hdr);
void print_str_table_32(Elf32_Ehdr *e_hdr);

#endif
