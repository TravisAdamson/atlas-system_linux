#include "2hreadelf.h"

void print_program_headers_64(Elf64_Ehdr *ehdr,
							Elf64_Phdr *phdr,
							Elf64_Shdr *shdr,
							const char *maps,
							int is_big_endian)
{
	char *segment_sections[ehdr->e_phnum];
	const char *shstrtab = maps + shdr[ehdr->e_shstrndx].sh_offset;

    initialize_segment_sections(segment_sections, ehdr->e_phnum);

    check_and_print_no_headers(ehdr);

    if (is_big_endian)
	{
        swap_endianess_64(phdr, ehdr->e_phnum);
	}
	print_top_section_64(ehdr, phdr, maps);

    map_sections_to_segments_64(ehdr, phdr, shdr, shstrtab, segment_sections);
}

void initialize_segment_sections(char *segment_sections[], int num_sections)
{
	int i;

	for (i = 0; i < num_sections; i++) {
		segment_sections[i] = malloc(4096);
		segment_sections[i][0] = '\0';
	}
}

void check_and_print_no_headers(Elf64_Ehdr *ehdr)
{
	if (!ehdr->e_phnum) {
		printf("\nThere are no program headers in this file.\n");
		return;
	}
}

void map_sections_to_segments_64(Elf64_Ehdr *ehdr, Elf64_Phdr *phdr, Elf64_Shdr *shdr,
                              const char *shstrtab, char *segment_sections[])
{
    int i, j;
    const char *section_name;

    for (i = 0; i < ehdr->e_shnum; i++) {
        section_name = shstrtab + shdr[i].sh_name;
        if (strcmp(section_name, ".gnu_debuglink") == 0 || strcmp(section_name, ".shstrtab") == 0) {
            continue;
        }
        for (j = 0; j < ehdr->e_phnum; j++) {
            if (shdr[i].sh_addr >= phdr[j].p_vaddr &&
                shdr[i].sh_addr < phdr[j].p_vaddr + phdr[j].p_memsz) {
                strcat(segment_sections[j], shstrtab + shdr[i].sh_name);
                if (i > 0)
                    strcat(segment_sections[j], " ");
            }
        }
    }

	print_segment_mapping_64(ehdr, segment_sections);
}

void print_segment_mapping_64(Elf64_Ehdr *ehdr, char *segment_sections[])
{
    int j;

    printf("\n");
    printf(" Section to Segment mapping:\n");
    printf("  Segment Sections...\n");
    for (j = 0; j < ehdr->e_phnum; j++) {
        printf("   %02d     %s\n", j, segment_sections[j]);
        free(segment_sections[j]);
    }
}
