#include "readelf.h"

void print_ver_32(Elf32_Ehdr *e_hdr)
{
	unsigned int new_ver;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_ver = __bswap_16(e_hdr->e_version);
	else
		new_ver = e_hdr->e_version;

	printf("%x\n", new_ver);
}

void print_entry_32(Elf32_Ehdr *e_hdr)
{
	unsigned int new_entry;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_entry = __bswap_16(e_hdr->e_entry);
	else
		new_entry = e_hdr->e_entry;

	printf("%x\n", new_entry);
}

void print_nprog_head_32(Elf32_Ehdr *e_hdr)
{
	unsigned int new_nprog;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_nprog = __bswap_16(e_hdr->e_phnum);
	else
		new_nprog = e_hdr->e_phnum;
	printf("%u\n", new_nprog);
}

void print_nsys_head_32(Elf32_Ehdr *e_hdr)
{
	unsigned int new_nsys;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_nsys = __bswap_16(e_hdr->e_shnum);
	else
		new_nsys = e_hdr->e_shnum;
	printf("%u\n", new_nsys);
}

void print_str_table_32(Elf32_Ehdr *e_hdr)
{
	unsigned int new_stri;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_stri = __bswap_16(e_hdr->e_shstrndx);
	else
		new_stri = e_hdr->e_shstrndx;
	printf("%u\n", new_stri);
}
