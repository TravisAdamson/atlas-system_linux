#include "2hreadelf.h"

void print_program_headers_32(Elf32_Ehdr *ehdr32,
							Elf32_Phdr *phdr32,
							Elf32_Shdr *shdr32,
							const char *maps,
							int is_big_endian)
{
	int i, j;
	char *segment_sections[ehdr32->e_phnum];
	const char *shstrtab;
	const char *section_name;

	if (!ehdr32->e_phnum)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}

	if (is_big_endian)
		swap_endianess_32(ehdr32, phdr32, shdr32, bswap_16(ehdr32->e_phnum));
	shstrtab = maps + shdr32[ehdr32->e_shstrndx].sh_offset;
	printf("\n");
	printf("Elf file type is %s\n", get_file_type(ehdr32->e_type));
	printf("Entry point 0x%x\n", ehdr32->e_entry);
	printf("There are %d program headers, starting at offset %d\n\n",
		ehdr32->e_phnum, ehdr32->e_phoff);

	printf("Program Headers:\n");
	printf("  %-14s %-8s %-10s %-10s %-7s %-7s %-3s %-8s\n",
       "Type", "Offset", "VirtAddr", "PhysAddr",
	   "FileSiz", "MemSiz", "Flg", "Align");
	for (i = 0; i < ehdr32->e_phnum; i++)
	{
		if (phdr32[i].p_align > 0)
		{
			printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %c%c%c 0x%x\n",
				get_segment_type(phdr32[i].p_type), phdr32[i].p_offset, phdr32[i].p_vaddr,
				phdr32[i].p_paddr, phdr32[i].p_filesz, phdr32[i].p_memsz,
				(phdr32[i].p_flags & PF_R) ? 'R' : ' ',
				(phdr32[i].p_flags & PF_W) ? 'W' : ' ',
				(phdr32[i].p_flags & PF_X) ? 'E' : ' ',
				phdr32[i].p_align);

			if (phdr32[i].p_type == PT_INTERP)
				printf("      [Requesting program interpreter: %s]\n", (char *)(maps + phdr32[i].p_offset));
		}
		else
		{
			printf("  %-14s 0x%06x 0x%08x 0x%08x 0x%05x 0x%05x %c%c%c 0\n",
				get_segment_type(phdr32[i].p_type), phdr32[i].p_offset, phdr32[i].p_vaddr,
				phdr32[i].p_paddr, phdr32[i].p_filesz, phdr32[i].p_memsz,
				(phdr32[i].p_flags & PF_R) ? 'R' : ' ',
				(phdr32[i].p_flags & PF_W) ? 'W' : ' ',
				(phdr32[i].p_flags & PF_X) ? 'E' : ' ');

			if (phdr32[i].p_type == PT_INTERP)
				printf("      [Requesting program interpreter: %s]\n", (char *)(maps + phdr32[i].p_offset));
		}
	}

	for (int i = 0; i < ehdr32->e_phnum; i++) {
		segment_sections[i] = malloc(4096);
		segment_sections[i][0] = '\0';
	}

	for (i = 0; i < ehdr32->e_shnum; i++) {
		section_name = shstrtab + shdr32[i].sh_name;
		if (strcmp(section_name, ".tm_clone_table") == 0)
		{
			continue;
		}
		if (strcmp(section_name, ".gnu_debuglink") == 0)
		{
			continue;
		}
		if (strcmp(section_name, ".shstrtab") == 0)
		{
			continue;
		}
		for (j = 0; j < ehdr32->e_phnum; j++) {
			if (shdr32[i].sh_addr >= phdr32[j].p_vaddr &&
				shdr32[i].sh_addr < phdr32[j].p_vaddr + phdr32[j].p_memsz) {
				strcat(segment_sections[j], shstrtab + shdr32[i].sh_name);
				if (i > 0)
					strcat(segment_sections[j], " ");
			}
		}
	}

	printf("\n");
	printf(" Section to Segment mapping:\n");
	printf("  Segment Sections...\n");
	for (j = 0; j < ehdr32->e_phnum; j++) {
		printf("   %02d     %s\n", j, segment_sections[j]);
		free(segment_sections[j]);
	}
}

void print_program_headers_64(Elf64_Ehdr *ehdr,
							Elf64_Phdr *phdr,
							Elf64_Shdr *shdr,
							const char *maps,
							int is_big_endian)
{
	int i, j;
	char *segment_sections[ehdr->e_phnum];
	const char *shstrtab = maps + shdr[ehdr->e_shstrndx].sh_offset;
	const char *section_name;

	if (!ehdr->e_phnum){
		printf("\nThere are no program headers in this file.\n");
		return;
	}

	if (is_big_endian)
		swap_endianess_64(phdr, ehdr->e_phnum);

	printf("\n");
	printf("Elf file type is %s\n", get_file_type(ehdr->e_type));
	printf("Entry point 0x%lx\n", ehdr->e_entry);
	printf("There are %d program headers, starting at offset %ld\n\n",
		ehdr->e_phnum, ehdr->e_phoff);

	printf("Program Headers:\n");
	printf("  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align\n");
	for (i = 0; i < ehdr->e_phnum; i++)
	{
		printf("  %-14s 0x%06lx 0x%016lx 0x%016lx 0x%06lx 0x%06lx %c%c%c 0x%lx\n",
			get_segment_type(phdr[i].p_type), phdr[i].p_offset, phdr[i].p_vaddr,
			phdr[i].p_paddr, phdr[i].p_filesz, phdr[i].p_memsz,
			(phdr[i].p_flags & PF_R) ? 'R' : ' ',
			(phdr[i].p_flags & PF_W) ? 'W' : ' ',
			(phdr[i].p_flags & PF_X) ? 'E' : ' ',
			phdr[i].p_align);

		if (phdr[i].p_type == PT_INTERP)
			printf("      [Requesting program interpreter: %s]\n", (char *)(maps + phdr[i].p_offset));
	}
	for (i = 0; i < ehdr->e_phnum; i++) {
		segment_sections[i] = malloc(4096);
		segment_sections[i][0] = '\0';
	}

	for (i = 0; i < ehdr->e_shnum; i++) {
		section_name = shstrtab + shdr[i].sh_name;
		if (strcmp(section_name, ".gnu_debuglink") == 0)
		{
			continue;
		}
		if (strcmp(section_name, ".shstrtab") == 0)
		{
			continue;
		}
		for (j = 0; j < ehdr->e_phnum; j++) {
			if (shdr[i].sh_addr >= phdr[j].p_vaddr &&
				shdr[i].sh_addr < phdr[j].p_vaddr + phdr[j].p_memsz) {
				strcat(segment_sections[j], shstrtab + shdr[i].sh_name);
				if (i > 0 )
					strcat(segment_sections[j], " ");
			}
		}
	}

	printf("\n");
	printf(" Section to Segment mapping:\n");
	printf("  Segment Sections...\n");
	for (j = 0; j < ehdr->e_phnum; j++) {
		printf("   %02d     %s\n", j, segment_sections[j]);
		free(segment_sections[j]);
	}
}
