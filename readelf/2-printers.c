#include "2hreadelf.h"

void print_top_section_64(Elf64_Ehdr *ehdr,
							Elf64_Phdr *phdr,
							const char *maps)
{
	int i;

	printf("\n");
	printf("Elf file type is %s\n", get_file_type(ehdr->e_type));
	printf("Entry point 0x%lx\n", ehdr->e_entry);
	printf("There are %d program headers, starting at offset %ld\n\n",
		ehdr->e_phnum, ehdr->e_phoff);

	printf("Program Headers:\n");
	printf("  %-14s %-8s %-10s %-10s %-7s %-7s %-3s %-5s\n",
		"Type", "Offset", "VirtAddr", "PhysAddr",
		"FileSiz", "MemSiz", "Flg", "Align");
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
			printf("      [Requesting program interpreter: %s]\n",
				(char *)(maps + phdr[i].p_offset));
	}
}
