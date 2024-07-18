#include "hobjdump.h"

void print_header_32(Elf32_Ehdr *ehdr, const char *filename)
{
	if (ehdr->e_type == 2)
	{
		printf("\n%s:     file format elf32-i386\n", filename);
		printf("architecture: i386, flags 0x00000112:\n");
		printf("EXEC_P, HAS_SYMS, D_PAGED\n");
	} else if (ehdr->e_type == 3)
	{
		printf("\n%s:     file format elf32-i386\n", filename);
		printf("architecture: i386, flags 0x00000150:\n");
		printf("HAS_SYMS, DYNAMIC, D_PAGED\n");
	} else if (ehdr->e_type == 1)
	{
		printf("\n%s:     file format elf32-i386\n", filename);
		printf("architecture: i386, flags 0x00000011:\n");
		printf("HAS_RELOC, HAS_SYMS\n");
	} else
	{
		printf("\n%s:     file format elf32-big\n", filename);
		printf("architecture: UNKNOWN!, flags 0x00000112:\n");
		printf("EXEC_P, HAS_SYMS, D_PAGED\n");
	}
	printf("start address 0x%08x\n\n", ehdr->e_entry);
}

void print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const unsigned char *maps,
					int is_big_endian, const char *filename)
{
	int i;
	const unsigned char *section_name, *shstrtab;
	Elf32_Shdr *section;

	if (is_big_endian)
		swap_endianess(ehdr, shdr, bswap_16(ehdr->e_shnum));
	print_header_32(ehdr, filename);
	shstrtab = (const unsigned char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);
	for (i = 0; i < ehdr->e_shnum; ++i)
	{
		section = &shdr[i];
		section_name = shstrtab + section->sh_name;
		if (strcmp((const char *)section_name, ".strtab") != 0 &&
			(strcmp((const char *)section_name, ".symtab") != 0) &&
			(strcmp((const char *)section_name, ".shstrtab") != 0) &&
			(strcmp((const char *)section_name, ".bss")) &&
			(strcmp((const char *)section_name, ".tm_clone_table")) &&
			(strcmp((const char *)section_name, ".rel.text")) &&
			(strcmp((const char *)section_name, ".rel.data")) &&
			(strcmp((const char *)section_name, ".rela.text.startup")) &&
			(strcmp((const char *)section_name, ".rela.debug.info")) &&
			(strcmp((const char *)section_name, ".rela.eh_frame")) &&
			(strncmp((const char *)section_name, ".rela.debug", 11)))
			if (section->sh_size > 0)
				print_section_contents_32(section, section_name, maps);
	}
}

void print_section_contents_32(Elf32_Shdr *section,
							const unsigned char *section_name,
							const unsigned char *maps)
{
	size_t i, j;

	if (strcmp((const char *)section_name, "") != 0)
		printf("Contents of section %s:\n", section_name);
	for (i = 0; i < section->sh_size; i += 16)
	{
		if ((section->sh_addr + i) > 0x1000)
			printf(" %lx ", (unsigned long)(section->sh_addr + i));
		else
			printf(" %04lx ", (unsigned long)(section->sh_addr + i));
		for (j = 0; j < 16; ++j)
		{
			if (i + j < section->sh_size)
				printf("%02x", maps[section->sh_offset + i + j]);
			else
				printf("  ");
			if (j % 4 == 3)
				printf(" ");
		}
		printf(" ");
		for (j = 0; j < 16 && i + j < section->sh_size; ++j)
		{
			if (maps[section->sh_offset + i + j] >= 32 &&
				maps[section->sh_offset + i + j] <= 126)
				printf("%c", maps[section->sh_offset + i + j]);
			else
				printf(".");
		}
		for (; j < 16; ++j)
			printf(" ");

		printf("\n");
	}
}

void print_section_contents_64(Elf64_Shdr *section,
							const unsigned char *section_name,
							const unsigned char *maps)
{
	size_t i, j;

	if (strcmp((const char *)section_name, "") != 0)
		printf("Contents of section %s:\n", section_name);
	for (i = 0; i < section->sh_size; i += 16)
	{
		if ((section->sh_addr + i) > 0x1000)
			printf(" %lx ", (unsigned long)(section->sh_addr + i));
		else
			printf(" %08lx ", (unsigned long)(section->sh_addr + i));
		for (j = 0; j < 16; ++j)
		{
			if (i + j < section->sh_size)
				printf("%02x", maps[section->sh_offset + i + j]);
			else
				printf("  ");
			if (j % 4 == 3)
				printf(" ");
		}
		printf(" ");
		for (j = 0; j < 16 && i + j < section->sh_size; ++j)
		{
			if (maps[section->sh_offset + i + j] >= 32 &&
				maps[section->sh_offset + i + j] <= 126)
				printf("%c", maps[section->sh_offset + i + j]);
			else
				printf(".");
		}
		for (; j < 16; ++j)
			printf(" ");

		printf("\n");
	}
}

void print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const unsigned char *maps,
			const char *filename)
{
	int i;
	const unsigned char *shstrtab, *section_name;
	Elf64_Shdr *section;

	printf("\n%s:     file format elf64-x86-64\n", filename);
	if (ehdr->e_type == 2)
	{
		printf("architecture: i386:x86-64, flags 0x00000112:\n");
		printf("EXEC_P, HAS_SYMS, D_PAGED\n");
	} else if (ehdr->e_type == 3)
	{
		printf("architecture: i386:x86-64, flags 0x00000150:\n");
		printf("HAS_SYMS, DYNAMIC, D_PAGED\n");
	} else if (ehdr->e_type == 1)
	{
		printf("architecture: i386:x86-64, flags 0x00000011:\n");
		printf("HAS_RELOC, HAS_SYMS\n");
	}
	printf("start address 0x%016lx\n\n", ehdr->e_entry);
	shstrtab = (const unsigned char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);
	for (i = 0; i < ehdr->e_shnum; ++i)
	{
		section = &shdr[i];
		section_name = shstrtab + section->sh_name;
		if (strcmp((const char *)section_name, ".strtab") != 0 &&
			(strcmp((const char *)section_name, ".symtab") != 0) &&
			(strcmp((const char *)section_name, ".shstrtab") != 0) &&
			(strcmp((const char *)section_name, ".bss")) &&
			(strcmp((const char *)section_name, ".tm_clone_table")) &&
			(strcmp((const char *)section_name, ".rel.text")) &&
			(strcmp((const char *)section_name, ".rel.data")) &&
			(strcmp((const char *)section_name, ".rela.text.startup")) &&
			(strcmp((const char *)section_name, ".rela.debug.info")) &&
			(strcmp((const char *)section_name, ".rela.eh_frame")) &&
			(strncmp((const char *)section_name, ".rela.debug", 11)))
			if (section->sh_size > 0)
				print_section_contents_64(section, section_name, maps);
	}
}
