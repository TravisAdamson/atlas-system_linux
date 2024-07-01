#include "2hreadelf.h"

const char *get_segment_type(uint32_t p_type)
{
	switch (p_type)
	{
	case PT_NULL:
		return ("NULL");
	case PT_LOAD:
		return ("LOAD");
	case PT_DYNAMIC:
		return ("DYNAMIC");
	case PT_INTERP:
		return ("INTERP");
	case PT_NOTE:
		return ("NOTE");
	case PT_SHLIB:
		return ("SHLIB");
	case PT_PHDR:
		return ("PHDR");
	case PT_TLS:
		return ("TLS");
	case PT_GNU_EH_FRAME:
		return ("GNU_EH_FRAME");
	case PT_GNU_STACK:
		return ("GNU_STACK");
	case PT_GNU_RELRO:
		return ("GNU_RELRO");
	default:
		return ("LOOS+464e550");
	}
}

const char *get_file_type(uint16_t e_type)
{
    switch (e_type)
	{
	case ET_NONE:
		return ("NONE (No file type)");
	case ET_REL:
		return ("REL (Relocatable file)");
	case ET_EXEC:
		return ("EXEC (Executable file)");
	case ET_DYN:
		return ("DYN (Shared object file)");
	case ET_CORE:
		return ("CORE (Core file)");
	default:
		return ("UNKNOWN");
    }
}

void swap_endianess_32(Elf32_Phdr *phdr, int phnum)
{
	int i;

	for (i = 0; i < phnum; i++)
	{
		phdr[i].p_type = bswap_32(phdr[i].p_type);
		phdr[i].p_offset = bswap_32(phdr[i].p_offset);
		phdr[i].p_vaddr = bswap_32(phdr[i].p_vaddr);
		phdr[i].p_paddr = bswap_32(phdr[i].p_paddr);
		phdr[i].p_filesz = bswap_32(phdr[i].p_filesz);
		phdr[i].p_memsz = bswap_32(phdr[i].p_memsz);
		phdr[i].p_flags = bswap_32(phdr[i].p_flags);
		phdr[i].p_align = bswap_32(phdr[i].p_align);
	}
}

void swap_endianess_64(Elf64_Phdr *phdr, int phnum)
{
	int i;

	for (i = 0; i < phnum; i++)
	{
		phdr[i].p_type = __bswap_32(phdr[i].p_type);
		phdr[i].p_offset = __bswap_64(phdr[i].p_offset);
		phdr[i].p_vaddr = __bswap_64(phdr[i].p_vaddr);
		phdr[i].p_paddr = __bswap_64(phdr[i].p_paddr);
		phdr[i].p_filesz = __bswap_64(phdr[i].p_filesz);
		phdr[i].p_memsz = __bswap_64(phdr[i].p_memsz);
		phdr[i].p_flags = __bswap_32(phdr[i].p_flags);
		phdr[i].p_align = __bswap_64(phdr[i].p_align);
	}
}

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

	if (!ehdr32->e_phnum){
		printf("\nThere are noprogram headers in this file.\n");
		return;
	}

	if (is_big_endian)
		swap_endianess_32(phdr32, bswap_16(ehdr32->e_phnum));
	shstrtab = maps + shdr32[ehdr32->e_shstrndx].sh_offset;
	printf("\n");
	printf("Elf file type is %s\n", get_file_type(ehdr32->e_type));
	printf("Entry point 0x%x\n", ehdr32->e_entry);
	printf("There are %d program headers, starting at offset %d\n\n",
		ehdr32->e_phnum, ehdr32->e_phoff);

	printf("Program Headers:\n");
	printf("  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align\n");
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
        	continue;
        for (j = 0; j < ehdr32->e_phnum; j++) {
            if (shdr32[i].sh_addr >= phdr32[j].p_vaddr &&
                shdr32[i].sh_addr < phdr32[j].p_vaddr + phdr32[j].p_memsz) {
                strcat(segment_sections[j], shstrtab + shdr32[i].sh_name);
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
        for (j = 0; j < ehdr->e_phnum; j++) {
            if (shdr[i].sh_addr >= phdr[j].p_vaddr &&
                shdr[i].sh_addr < phdr[j].p_vaddr + phdr[j].p_memsz) {
                strcat(segment_sections[j], shstrtab + shdr[i].sh_name);
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

int main(int argc, char **argv)
{
	const char *filename;
	int fd, is_64_bit, is_big_endian;
	struct stat st;
	size_t filesize;
	void *maps;
	Elf64_Ehdr *ehdr;
	Elf32_Ehdr *ehdr32;
	Elf64_Phdr *phdr;
	Elf32_Phdr *phdr32;
	Elf64_Shdr *shdr64;
	Elf32_Shdr *shdr32;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
		return (EXIT_FAILURE);
	}

	filename = argv[1];
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}

	if (fstat(fd, &st) == -1)
	{
		perror("fstat");
		close(fd);
		return (EXIT_FAILURE);
	}

	filesize = st.st_size;
	maps = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (maps == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return (EXIT_FAILURE);
	}

	close(fd);

	ehdr = (Elf64_Ehdr *)maps;

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		ehdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		fprintf(stderr, "Not a valid ELF file\n");
		munmap(maps, filesize);
		return (EXIT_FAILURE);
	}

	is_big_endian = (ehdr->e_ident[EI_DATA] == ELFDATA2MSB);
	is_64_bit = (ehdr->e_ident[EI_CLASS] == ELFCLASS64);

	if (is_64_bit)
	{
		phdr = (Elf64_Phdr *)((uint8_t *)maps + ehdr->e_phoff);
		shdr64 = (Elf64_Shdr *)((uint8_t *)maps + ehdr->e_shoff);
		print_program_headers_64(ehdr, phdr, shdr64, maps, is_big_endian);
	}
	else
	{
		ehdr32 = (Elf32_Ehdr *)maps;
		phdr32 = (Elf32_Phdr *)((uint8_t *)maps + ehdr32->e_phoff);
		shdr32 = (Elf32_Shdr *)((uint8_t *)maps + ehdr32->e_shoff);
		print_program_headers_32(ehdr32, phdr32, shdr32, maps, is_big_endian);
	}

	munmap(maps, filesize);
	return EXIT_SUCCESS;
}
