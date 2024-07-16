#include "hnm.h"

char get_type_32(Elf32_Sym s_table, Elf32_Shdr *shdr)
{
	char type;

	if (ELF32_ST_BIND(s_table.st_info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF32_ST_BIND(s_table.st_info) == STB_WEAK &&
			 ELF32_ST_TYPE(s_table.st_info) == STT_OBJECT)
		type = s_table.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF32_ST_BIND(s_table.st_info) == STB_WEAK)
		type = s_table.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (s_table.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (s_table.st_shndx == SHN_ABS)
		type = 'A';
	else if (s_table.st_shndx == SHN_COMMON)
		type = 'C';
	else if (shdr[s_table.st_shndx].sh_type == SHT_NOBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'B';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == SHF_ALLOC)
		type = 'R';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'D';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		type = 'T';
	else if (shdr[s_table.st_shndx].sh_type == SHT_DYNAMIC)
		type = 'D';
	else
		type = 'T';
	if (ELF32_ST_BIND(s_table.st_info) == STB_LOCAL && type != '?')
		type += 32;
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
	ehdr->e_shoff = bswap_32(ehdr->e_shoff);
}

char get_type_64(Elf64_Sym s_table, Elf64_Shdr *shdr)
{
	char type;

	if (ELF64_ST_BIND(s_table.st_info) == STB_GNU_UNIQUE)
		type = 'u';
	else if (ELF64_ST_BIND(s_table.st_info) == STB_WEAK &&
			 ELF64_ST_TYPE(s_table.st_info) == STT_OBJECT)
		type = s_table.st_shndx == SHN_UNDEF ? 'v' : 'V';
	else if (ELF64_ST_BIND(s_table.st_info) == STB_WEAK)
		type = s_table.st_shndx == SHN_UNDEF ? 'w' : 'W';
	else if (s_table.st_shndx == SHN_UNDEF)
		type = 'U';
	else if (s_table.st_shndx == SHN_ABS)
		type = 'A';
	else if (s_table.st_shndx == SHN_COMMON)
		type = 'C';
	else if (shdr[s_table.st_shndx].sh_type == SHT_NOBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'B';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == SHF_ALLOC)
		type = 'R';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_WRITE))
		type = 'D';
	else if (shdr[s_table.st_shndx].sh_type == SHT_PROGBITS &&
			 shdr[s_table.st_shndx].sh_flags == (SHF_ALLOC | SHF_EXECINSTR))
		type = 'T';
	else if (shdr[s_table.st_shndx].sh_type == SHT_DYNAMIC)
		type = 'D';
	else
		type = 'T';
	if (ELF64_ST_BIND(s_table.st_info) == STB_LOCAL && type != '?')
		type += 32;
	return (type);
}
