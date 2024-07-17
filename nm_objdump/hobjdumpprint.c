#include "hobjdump.h"

int print_32(Elf32_Ehdr *ehdr, Elf32_Shdr *shdr, const char *maps,
					 int is_big_endian)
{
	int i;
	const char *section_name, *shstrtab;

	if (is_big_endian)
		swap_endianess(ehdr, shdr, bswap_32(ehdr->e_shoff));

	printf("File format: ELF32-i386\n");
    printf("architecture: i386, flags 0x%08x:\n", ehdr->e_flags);
    printf("start address 0x%08x\n\n", ehdr->e_entry);

    shstrtab = (const char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);

    for (i = 0; i < ehdr->e_shnum; i++)
	{
        section_name = shstrtab + shdr[i].sh_name;
        if (shdr[i].sh_size > 0)
		{
            printf("Contents of section %s:\n", section_name);
            print_section(maps + shdr[i].sh_offset, shdr[i].sh_size, shdr[i].sh_addr);
        }
    }
	return (0);
}

void print_section(const char *section, int size, int address)
{
	int i, line_size;

    for (i = 0; i < size; i += 16) {
        line_size = (size - i) < 16 ? (size - i) : 16;
        print_hex_ascii_line(section + i, line_size, address + i);
    }
}

void print_hex_ascii_line(const char *data, int len, int offset)
{
    int i;

    printf("  %07x ", offset);
    for (i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    for (; i < 16; i++) {
        printf("   ");
    }
    printf(" ");
    for (i = 0; i < len; i++) {
        if (data[i] >= 32 && data[i] <= 126) {
            printf("%c", data[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

int print_64(Elf64_Ehdr *ehdr, Elf64_Shdr *shdr, const char *maps)
{
	int i;
	const char *shstrtab, *section_name;

    printf("File format: ELF64-x86-64\n");
    printf("architecture: x86-64, flags 0x%08x:\n", ehdr->e_flags);
    printf("start address 0x%016lx\n\n", ehdr->e_entry);

    shstrtab = (const char *)(maps + shdr[ehdr->e_shstrndx].sh_offset);

    for (i = 0; i < ehdr->e_shnum; i++) {
        section_name = shstrtab + shdr[i].sh_name;
        if (shdr[i].sh_size > 0) {
            printf("Contents of section %s:\n", section_name);
            print_section(maps + shdr[i].sh_offset, shdr[i].sh_size, shdr[i].sh_addr);
        }
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
