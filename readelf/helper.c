#include "1hreadelf.h"

void process_elf(void *maps, size_t filesize) {
    Elf64_Ehdr *ehdr = (Elf64_Ehdr *)maps;
	int is_big_endian, is_64_bit;
    (void)filesize;
    
	check_elf_magic(ehdr);
    is_big_endian = (ehdr->e_ident[EI_DATA] == ELFDATA2MSB);
    is_64_bit = (ehdr->e_ident[EI_CLASS] == ELFCLASS64);
    if (is_64_bit)
        process_elf64(ehdr, is_big_endian, maps);
    else
        process_elf32((Elf32_Ehdr *)ehdr, is_big_endian, maps);
}

void process_elf64(Elf64_Ehdr *ehdr, int is_big_endian, void *maps) {
    Elf64_Shdr *shdr = (Elf64_Shdr *)((uint8_t *)maps + ehdr->e_shoff);
    const char *strtab = (const char *)((uint8_t *)maps + shdr[ehdr->e_shstrndx].sh_offset);

    if (is_big_endian)
        swap_endianess_64(shdr, ehdr->e_shnum);

    print_section_headers_64(ehdr, shdr, strtab);
}

void process_elf32(Elf32_Ehdr *ehdr32, int is_big_endian, void *maps)
{
    Elf32_Shdr *shdr32 = (Elf32_Shdr *)((uint8_t *)maps + ehdr32->e_shoff);
    const char *strtab = (const char *)((uint8_t *)maps + shdr32[ehdr32->e_shstrndx].sh_offset);

    if (is_big_endian)
        swap_endianess_32(shdr32, ehdr32->e_shnum);

    print_section_headers_32(ehdr32, shdr32, strtab);
}

void swap_endianess_64(Elf64_Shdr *shdr, int shnum)
{
	int i = 0;

    for (i = 0; i < shnum; i++)
	{
        shdr[i].sh_name = bswap_32(shdr[i].sh_name);
        shdr[i].sh_type = bswap_32(shdr[i].sh_type);
        shdr[i].sh_addr = bswap_64(shdr[i].sh_addr);
        shdr[i].sh_offset = bswap_64(shdr[i].sh_offset);
        shdr[i].sh_size = bswap_64(shdr[i].sh_size);
        shdr[i].sh_entsize = bswap_64(shdr[i].sh_entsize);
        shdr[i].sh_flags = bswap_64(shdr[i].sh_flags);
        shdr[i].sh_link = bswap_32(shdr[i].sh_link);
        shdr[i].sh_info = bswap_32(shdr[i].sh_info);
        shdr[i].sh_addralign = bswap_64(shdr[i].sh_addralign);
    }
}

void swap_endianess_32(Elf32_Shdr *shdr, int shnum) 
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
}