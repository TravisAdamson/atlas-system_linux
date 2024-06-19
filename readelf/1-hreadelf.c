#include "1hreadelf.h"

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
	printf("[Nr] %-19s %-15s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",
		   "Name", "Type", "Addr", "Off", "Size",
		   "ES", "Flg", "Lk", "Inf", "Al");
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		name = (char *)(strtab + shdr[i].sh_name);
		printf("[%2d] %-19s %-15u %08x %06x %06x %02x %3x %2u %3u %2u\n",
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
	printf("[Nr] %-19s %-15s %-8s %-6s %-6s %-2s %-3s %-2s %-3s %-2s\n",
		   "Name", "Type", "Addr", "Off", "Size",
		   "ES", "Flg", "Lk", "Inf", "Al");
	for (i = 0; i < ehdr->e_shnum; i++)
	{
		name = (char *)(strtab + shdr[i].sh_name);
		printf("[%2d] %-19s %-15u %016lx %06lx %06lx %02lx %3lx %2u %3u %2lu\n",
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
 * main - The primary function
 * @argc: Number of arguements given
 * @argv: Array of arguments
 * Return: 1 for failure, 0 for success
*/

int main(int argc, char **argv)
{
	const char *filename = NULL;
	int fd, is_64_bit, is_big_endian, i;
	struct stat st;
	size_t filesize;
	void *maps;
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdr;
	const char *strtab;
	Elf32_Ehdr *ehdr32;
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
	maps = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
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
		shdr = (Elf64_Shdr *)((uint8_t *)maps + ehdr->e_shoff);
		strtab = (const char *)((uint8_t *)maps + shdr[ehdr->e_shstrndx].sh_offset);

		if (is_big_endian)
		{
			for (i = 0; i < ehdr->e_shnum; i++)
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
		print_section_headers_64(ehdr, shdr, strtab);
	}
	else
	{
		ehdr32 = (Elf32_Ehdr *)ehdr;
		shdr32 = (Elf32_Shdr *)((uint8_t *)maps + ehdr32->e_shoff);
		strtab = (const char *)((uint8_t *)maps + shdr32[ehdr32->e_shstrndx].sh_offset);

		if (is_big_endian)
		{
			for (i = 0; i < ehdr32->e_shnum; i++)
			{
				shdr32[i].sh_name = bswap_32(shdr32[i].sh_name);
				shdr32[i].sh_type = bswap_32(shdr32[i].sh_type);
				shdr32[i].sh_addr = bswap_32(shdr32[i].sh_addr);
				shdr32[i].sh_offset = bswap_32(shdr32[i].sh_offset);
				shdr32[i].sh_size = bswap_32(shdr32[i].sh_size);
				shdr32[i].sh_entsize = bswap_32(shdr32[i].sh_entsize);
				shdr32[i].sh_flags = bswap_32(shdr32[i].sh_flags);
				shdr32[i].sh_link = bswap_32(shdr32[i].sh_link);
				shdr32[i].sh_info = bswap_32(shdr32[i].sh_info);
				shdr32[i].sh_addralign = bswap_32(shdr32[i].sh_addralign);
			}
		}
		print_section_headers_32(ehdr32, shdr32, strtab);
	}

	munmap(maps, filesize);
	return (EXIT_SUCCESS);
}
