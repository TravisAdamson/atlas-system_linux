#include "hnm.h"

int print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					 int is_big_endian)
{
	Elf32_Shdr *sym_shdr = NULL;
	Elf32_Sym *s_table;
	int i, num_symbols;
	char *strtab;

	(void)maps;
	if (is_big_endian)
		swap_endianess(ehdr, shdr, bswap_16(ehdr->e_shnum));

	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			sym_shdr = (Elf32_Shdr *)&shdr[i];
			break;
		}
	}
	if (!sym_shdr)
		return (-1);
	strtab = STRING_TABLE(ehdr, shdr, sym_shdr);
	s_table = SYMBOL_TABLE(ehdr, sym_shdr);
	num_symbols = SYMBOL_COUNT(sym_shdr);
	print_tables_32(num_symbols, s_table, strtab, shdr);
	return (0);
}

void print_tables_32(int num_symbols, Elf32_Sym *s_table,
					 char *strtab, Elf32_Shdr *shdr)
{
	int i;
	char type;

	for (i = 0; i < num_symbols; i++)
	{
		type = get_type_32(s_table[i]);
		if (type == 'D' && shdr[s_table[i].st_shndx].sh_type == SHT_NOBITS)
			printf("%08x %c %s\n",
			s_table[i].st_value, 'B', strtab + s_table[i].st_name);
		else if (type == 'a' || !s_table[i].st_name)
			continue;
		else if (type == 'A' && s_table[i].st_value == 0)
			continue;
		else if (strcmp("main.c", strtab + s_table[i].st_name) == 0)
			continue;
		else if (type == 'w' || type == 'U')
			printf("%8s %c %s\n",
			"", type, strtab + s_table[i].st_name);
		else
			printf("%08x %c %s\n",
			s_table[i].st_value, type, strtab + s_table[i].st_name);
	}
}

int print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps)
{
	Elf64_Shdr *sym_shdr;
	Elf64_Sym *s_table;
	int i, num_symbols;
	char *strtab;

	(void)maps;
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			sym_shdr = (Elf64_Shdr *)&shdr[i];
			break;
		}
	}
	if (!sym_shdr)
		return (-1);
	strtab = STRING_TABLE(ehdr, shdr, sym_shdr);
	s_table = SYMBOL_TABLE64(ehdr, sym_shdr);
	num_symbols = SYMBOL_COUNT64(sym_shdr);
	print_tables_64(num_symbols, s_table, strtab, shdr);
	return (0);
}

void print_tables_64(int num_symbols, Elf64_Sym *s_table,
					 char *strtab, Elf64_Shdr *shdr)
{
	int i;
	char type;

	for (i = 0; i < num_symbols; i++)
	{
		type = get_type_64(s_table[i]);
		if (type == 'D' && shdr[s_table[i].st_shndx].sh_type == SHT_NOBITS)
			printf("%016lx %c %s\n",
			s_table[i].st_value, 'B', strtab + s_table[i].st_name);
		else if (type == 'a' || !s_table[i].st_name)
			continue;
		else if (type == 'A' && s_table[i].st_value == 0)
			continue;
		else if (strcmp("main.c", strtab + s_table[i].st_name) == 0)
			continue;
		else if (type == 'w' || type == 'U')
			printf("%16s %c %s\n",
			"", type, strtab + s_table[i].st_name);
		else
			printf("%016lx %c %s\n",
			s_table[i].st_value, type, strtab + s_table[i].st_name);
	}
}
