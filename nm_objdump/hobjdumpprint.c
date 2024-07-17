#include "hobjdump.h"

int print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					int is_big_endian)
{
	int i;
	const char *section_name, *shstrtab;
	Elf32_Shdr *section;

	if (is_big_endian)
		swap_endianess(ehdr, shdr, bswap_32(ehdr->e_shoff));

	printf("File format: ELF32-i386\n");
	printf("architecture: i386, flags 0x%08x:\n", ehdr->e_flags);
	printf("start address 0x%08x\n\n", ehdr->e_entry);

	shstrtab = (const char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);

    for (i = 0; i < ehdr->e_shnum; ++i) {
        section = &shdr[i];
        section_name = shstrtab + section->sh_name;
        print_section_contents_32(section, section_name, maps);
    }

	return (0);
}

void print_section_contents_32(Elf32_Shdr *section, const char *section_name, const char *maps)
{
	size_t i, j;

    printf("Contents of section %s:\n", section_name);
    for (i = 0; i < section->sh_size; i += 16)
	{
        printf(" %08lx ", section->sh_addr + i);
        for (j = 0; j < 16; ++j)
		{
            if (i + j < section->sh_size)
                printf("%02x", maps[i + j]);
            else
                printf("  ");
            if (j % 4 == 3) printf(" ");
        }
        printf(" ");
        for (j = 0; j < 16 && i + j < section->sh_size; ++j)
		{
            if (maps[i + j] >= 32 && maps[i + j] <= 126)
                printf("%c", maps[i + j]);
            else
                printf(".");
        }
        printf("\n");
    }
}

void print_section_contents_64(Elf64_Shdr *section, const char *section_name, const char *maps)
{
	size_t i, j;

    printf("Contents of section %s:\n", section_name);
    for (i = 0; i < section->sh_size; i += 16)
	{
        printf(" %08lx ", section->sh_addr + i);
        for (j = 0; j < 16; ++j)
		{
            if (i + j < section->sh_size)
                printf("%02x", maps[i + j]);
            else
                printf("  ");
            if (j % 4 == 3) printf(" ");
        }
        printf(" ");
        for (j = 0; j < 16 && i + j < section->sh_size; ++j)
		{
            if (maps[i + j] >= 32 && maps[i + j] <= 126)
                printf("%c", maps[i + j]);
            else
                printf(".");
        }
        printf("\n");
    }
}

int print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps)
{
	int i;
	const char *shstrtab, *section_name;
	Elf64_Shdr *section;

	printf("File format: ELF64-x86-64\n");
	printf("architecture: x86-64, flags 0x%08x:\n", ehdr->e_flags);
	printf("start address 0x%016lx\n\n", ehdr->e_entry);

	shstrtab = (const char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);

    for (i = 0; i < ehdr->e_shnum; ++i) {
        section = &shdr[i];
        section_name = shstrtab + section->sh_name;
        print_section_contents_64(section, section_name, maps);
    }
	return (0);
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
