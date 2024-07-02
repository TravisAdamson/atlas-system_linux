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

void print_program_headers_64(Elf64_Ehdr * ehdr,
							Elf64_Phdr * phdr,
							Elf64_Shdr * shdr,
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
void initialize_segment_sections(char *segment_sections[], int num_sections);
void print_segment_mapping_64(Elf64_Ehdr *ehdr, char *segment_sections[]);
void map_sections_to_segments_64(Elf64_Ehdr *ehdr, Elf64_Phdr *phdr,
							Elf64_Shdr *shdr, const char *shstrtab,
							char *segment_sections[]);
void print_top_section_64(Elf64_Ehdr *ehdr,
							Elf64_Phdr *phdr,
							const char *maps);


void print_program_headers_info_32(Elf32_Ehdr *ehdr32);
void print_program_headers_32_2(Elf32_Phdr *phdr32, int e_phnum,
							const char *maps);
void map_sections_to_segments_32(char **segment_sections, Elf32_Phdr *phdr32,
							int e_phnum, Elf32_Shdr *shdr32,
							const char *shstrtab, Elf32_Ehdr *ehdr32);
void print_segment_mapping_32(char **segment_sections, int e_phnum);
void setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr *ehdr,
					const char *maps);

#endif
