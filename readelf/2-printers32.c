#include "2hreadelf.h"

void print_program_headers_info_32(Elf32_Ehdr *ehdr32)
{
    printf("\nElf file type is %s\n", get_file_type(ehdr32->e_type));
    printf("Entry point 0x%x\n", ehdr32->e_entry);
    printf("There are %d program headers, starting at offset %d\n\n",
        ehdr32->e_phnum, ehdr32->e_phoff);
}

void print_program_headers_32_2(Elf32_Phdr *phdr32, int e_phnum, const char *maps)
{
    int i;

    printf("Program Headers:\n");
    printf("  %-14s %-8s %-10s %-10s %-7s %-7s %-3s %-5s\n",
        "Type", "Offset", "VirtAddr", "PhysAddr",
        "FileSiz", "MemSiz", "Flg", "Align");

    for (i = 0; i < e_phnum; i++)
	{
        printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %c%c%c",
            get_segment_type(phdr32[i].p_type), phdr32[i].p_offset, phdr32[i].p_vaddr,
            phdr32[i].p_paddr, phdr32[i].p_filesz, phdr32[i].p_memsz,
            (phdr32[i].p_flags & PF_R) ? 'R' : ' ',
            (phdr32[i].p_flags & PF_W) ? 'W' : ' ',
            (phdr32[i].p_flags & PF_X) ? 'E' : ' ');

        if (phdr32[i].p_align > 0)
		{
            printf(" 0x%x\n", phdr32[i].p_align);
        } else
		{
            printf(" 0\n");
        }

        if (phdr32[i].p_type == PT_INTERP)
		{
            printf("      [Requesting program interpreter: %s]\n",
                (char *)(maps + phdr32[i].p_offset));
        }
    }
}

void map_sections_to_segments_32(char **segment_sections, Elf32_Phdr *phdr32, int e_phnum,
                              Elf32_Shdr *shdr32, const char *shstrtab, Elf32_Ehdr *ehdr32)
{
    int i, j;
    const char *section_name;

    for (i = 0; i < ehdr32->e_shnum; i++)
	{
        section_name = shstrtab + shdr32[i].sh_name;
        if (strcmp(section_name, ".tm_clone_table") == 0 ||
            strcmp(section_name, ".gnu_debuglink") == 0 ||
            strcmp(section_name, ".shstrtab") == 0)
		{
            continue;
        }
        for (j = 0; j < e_phnum; j++)
		{
            if (shdr32[i].sh_addr >= phdr32[j].p_vaddr &&
                shdr32[i].sh_addr < phdr32[j].p_vaddr + phdr32[j].p_memsz)
			{
                strcat(segment_sections[j], section_name);
                if (i > 0)
                    strcat(segment_sections[j], " ");
            }
        }
    }

	print_segment_mapping_32(segment_sections, e_phnum);
}

void print_segment_mapping_32(char **segment_sections, int e_phnum)
{
    int j;

    printf("\n");
    printf(" Section to Segment mapping:\n");
    printf("  Segment Sections...\n");

    for (j = 0; j < e_phnum; j++)
	{
        printf("   %02d     %s\n", j, segment_sections[j]);
        free(segment_sections[j]);
    }
}

void print_program_headers_32(Elf32_Ehdr *ehdr32,
                            Elf32_Phdr *phdr32,
                            Elf32_Shdr *shdr32,
                            const char *maps,
                            int is_big_endian)
{
    int i;
    char *segment_sections[ehdr32->e_phnum];
    const char *shstrtab;

    if (!ehdr32->e_phnum) {
        printf("\nThere are no program headers in this file.\n");
        return;
    }

    if (is_big_endian)
        swap_endianess_32(ehdr32, phdr32, shdr32, bswap_16(ehdr32->e_phnum));
    shstrtab = maps + shdr32[ehdr32->e_shstrndx].sh_offset;

    print_program_headers_info_32(ehdr32);

    for (i = 0; i < ehdr32->e_phnum; i++) {
        segment_sections[i] = malloc(4096);
        segment_sections[i][0] = '\0';
    }

    print_program_headers_32_2(phdr32, ehdr32->e_phnum, maps);

    map_sections_to_segments_32(segment_sections, phdr32, ehdr32->e_phnum, shdr32, shstrtab, ehdr32);
}
