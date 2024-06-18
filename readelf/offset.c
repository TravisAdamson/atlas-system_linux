#include "readelf.h"

void print_offset_32(Elf32_Ehdr *e_hdr)
{
	Elf32_Off sect_off = e_hdr->e_shoff;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		sect_off = __bswap_32(e_hdr->e_shoff);
	printf("%u (bytes into file)\n", sect_off);
}

void print_offset_64(Elf64_Ehdr *e_hdr)
{
	Elf64_Off sect_off =  e_hdr->e_shoff;

	printf("%lu (bytes into file)\n", sect_off);
}

void print_poffset_32(Elf32_Ehdr *e_hdr)
{
	Elf32_Off prog_off = e_hdr->e_phoff;

	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		prog_off = __bswap_32(e_hdr->e_phoff);
	printf("%u (bytes into file)\n", prog_off);
}

void print_poffset_64(Elf64_Ehdr *e_hdr)
{
	Elf64_Off prog_off = e_hdr->e_phoff;

	printf("%lu (bytes into file)\n", prog_off);
}
