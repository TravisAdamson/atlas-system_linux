#include "1hreadelf.h"

void *open_and_map_file(const char *filename, size_t *filesize) {
	int fd;
	void *maps;
	struct stat st;
	fd = open(filename, O_RDONLY);
	if (fd == -1) {
		perror("open");
		return NULL;
	}

	if (fstat(fd, &st) == -1) {
		perror("fstat");
		close(fd);
		return NULL;
	}

	*filesize = st.st_size;
	maps = mmap(NULL, *filesize, PROT_READ, MAP_PRIVATE, fd, 0);
	if (maps == MAP_FAILED)
	{
		perror("mmap");
		close(fd);
		return NULL;
	}

	close(fd);
	return maps;
}

void check_elf_magic(Elf64_Ehdr *ehdr)
{
	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 ||
		ehdr->e_ident[EI_MAG1] != ELFMAG1 ||
		ehdr->e_ident[EI_MAG2] != ELFMAG2 ||
		ehdr->e_ident[EI_MAG3] != ELFMAG3) {
		fprintf(stderr, "Not a valid ELF file\n");
		exit(EXIT_FAILURE);
	}
}
/**
 * print_section_headers_32 - Print the 32 bit section headers
 * @ehdr: 32 bit elf header
 * @shdr: 32 bit section headers
 * @strtab: formating string
*/

void print_section_headers_32(Elf32_Ehdr *ehdr,
							Elf32_Shdr *shdr,
							const char *strtab)
{
	int i = 0;
	char *name = NULL;

	printf("There are %d section headers, starting at offset 0x%u:\n",
		ehdr->e_shnum, ehdr->e_shoff);
	printf("[Nr] %-17s %-20s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",
		"Name", "Type", "Addr", "Off", "Size",
		"ES", "Flg", "Lk", "Inf", "Al");
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		name = (char *)(strtab + shdr[i].sh_name);
		printf("[%2d] %-17s %-20u %08x %06x %06x %02x %3x %2u %3u %2u\n",
			i,
			name,
			shdr[i].sh_type,
			shdr[i].sh_addr,
			shdr[i].sh_offset,
			shdr[i].sh_size,
			shdr[i].sh_entsize,
			shdr[i].sh_flags,
			shdr[i].sh_link,
			shdr[i].sh_info,
			shdr[i].sh_addralign);
	}
}

/**
 * print_section_headers_64 - Print the 64 bit section headers
 * @ehdr: 64 bit elf header
 * @shdr: 64 bit section headers
 * @strtab: formating string
*/

void print_section_headers_64(Elf64_Ehdr *ehdr,
							Elf64_Shdr *shdr,
							const char *strtab)
{
	int i = 0;
	char *name = NULL;

	printf("There are %d section headers, starting at offset 0x%lu:\n",
		ehdr->e_shnum, ehdr->e_shoff);
	printf("[Nr] %-17s %-20s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",
		"Name", "Type", "Addr", "Off", "Size",
		"ES", "Flg", "Lk", "Inf", "Al");
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		name = (char *)(strtab + shdr[i].sh_name);
		printf("[%2d] %-17s %-20u %016lx %06lx %06lx %02lx %3lx %2u %3u %2lu\n",
			i,
			name,
			shdr[i].sh_type,
			shdr[i].sh_addr,
			shdr[i].sh_offset,
			shdr[i].sh_size,
			shdr[i].sh_entsize,
			shdr[i].sh_flags,
			shdr[i].sh_link,
			shdr[i].sh_info,
			shdr[i].sh_addralign);
	}
}
