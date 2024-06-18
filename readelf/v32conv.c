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