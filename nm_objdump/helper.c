#include "hnm.h"

char get_type_32(Elf32_Sym s_table)
{
	char type;

	switch (ELF32_ST_TYPE(s_table.st_info))
	{
		case STT_NOTYPE:
			type = 'T';
			break;
		case STT_OBJECT:
			type = 'D';
			break;
		case STT_FUNC:
			type = 'T';
			break;
		case STT_SECTION:
			type = 'T';
			break;
		case STT_FILE:
			type = ' ';
			break;
		default:
			type = 'U';
	}
	if (ELF32_ST_BIND(s_table.st_info) == STB_LOCAL)
	{
		if (type == 'T')
			type = 't';
		else if (type == 'D')
			type = 'd';
	}
	else if (ELF32_ST_BIND(s_table.st_info) == STB_WEAK)
	{
		if (type == 'T')
			type = 'W';
		if (type == 'D')
			type = 'B';
	}
	if (s_table.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (s_table.st_shndx == SHN_ABS)
		type = 'A';
	else if (s_table.st_shndx == SHN_COMMON)
		type = 'C';
	return (type);
}

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
}
