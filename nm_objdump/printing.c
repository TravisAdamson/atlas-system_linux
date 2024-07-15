#include "hnm.h"

void print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					 int is_big_endian)
{
	Elf32_Shdr *sym_shdr, *dynsym_shdr, *strtab_shdr;
	Elf32_Sym *s_table, *ds_table;
	int i, num_symbols, num_symbols_d;
	char *strtab;

	if (is_big_endian)
		swap_endianess(ehdr, shdr, bswap_16(ehdr->e_shnum));

	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_SYMTAB)
		{
			sym_shdr = &shdr[i];
        } else if (shdr[i].sh_type == SHT_STRTAB && strcmp(".strtab",
				   (char *)maps + shdr[ehdr->e_shstrndx].sh_offset +
				   shdr[i].sh_name) == 0)
		{
        	strtab_shdr = &shdr[i];
		}
	}
	if (strtab_shdr)
		strtab = (char *)maps + strtab_shdr->sh_offset;
	if (sym_shdr)
	{
		s_table = (Elf32_Sym *)((char *)maps + sym_shdr->sh_offset);
		num_symbols = sym_shdr->sh_size / sizeof (Elf32_Sym);
		print_tables_32(num_symbols, s_table, is_big_endian, strtab);
	}
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr[i].sh_type == SHT_DYNSYM)
		{
			dynsym_shdr = &shdr[i];
			break;
		}
	}

	if (dynsym_shdr)
	{
		ds_table = (Elf32_Sym *)((char *)maps + dynsym_shdr->sh_offset);
		num_symbols_d = dynsym_shdr->sh_size / sizeof (Elf32_Sym);
		print_tables_32(num_symbols_d, ds_table, is_big_endian, strtab);
	}
}

void print_tables_32(int num_symbols, Elf32_Sym *s_table,
					 int is_big_endian, char *strtab)
{
	int i;
	char type;

	(void)is_big_endian;
	for (i = 0; i < num_symbols; i++)
	{
		type = get_type_32(s_table[i]);
		printf("%08x %c %s\n",
			s_table[i].st_value, type, &strtab[s_table[i].st_name]);
	}
}
