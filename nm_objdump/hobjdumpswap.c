#include "hobjdump.h"

void swap_endianess(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, int shnum)
{
	int i = 0;

	for (i = 0; i < shnum; i++)
	{
		shdr[i].sh_name = bswap_32(shdr[i].sh_name);
		shdr[i].sh_type = bswap_32(shdr[i].sh_type);
		shdr[i].sh_addr = bswap_32(shdr[i].sh_addr);
		shdr[i].sh_offset = bswap_32(shdr[i].sh_offset);
		shdr[i].sh_size = bswap_32(shdr[i].sh_size);
		shdr[i].sh_entsize = bswap_32(shdr[i].sh_entsize);
		shdr[i].sh_flags = bswap_32(shdr[i].sh_flags);
		shdr[i].sh_link = bswap_32(shdr[i].sh_link);
		shdr[i].sh_info = bswap_32(shdr[i].sh_info);
		shdr[i].sh_addralign = bswap_32(shdr[i].sh_addralign);
	}

	ehdr->e_shnum = bswap_16(ehdr->e_shnum);
	ehdr->e_shstrndx = bswap_16(ehdr->e_shstrndx);
	ehdr->e_shoff = bswap_32(ehdr->e_shoff);
	ehdr->e_entry = bswap_32(ehdr->e_entry);
}
