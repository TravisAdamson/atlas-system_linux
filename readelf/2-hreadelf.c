#include "2hreadelf.h"

/**
 * main - The primary function
 * @argc: Number of arguements given
 * @argv: Array of arguments
 * Return: 1 for failure, 0 for success
*/

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
		if (is_big_endian)
		{
			ehdr32 = (Elf32_Ehdr *)maps;
			phdr32 = (Elf32_Phdr *)((uint8_t *)maps + bswap_32(ehdr32->e_phoff));
			shdr32 = (Elf32_Shdr *)((uint8_t *)maps + bswap_32(ehdr32->e_shoff));
		}
		else
		{
			ehdr32 = (Elf32_Ehdr *)maps;
			phdr32 = (Elf32_Phdr *)((uint8_t *)maps + ehdr32->e_phoff);
			shdr32 = (Elf32_Shdr *)((uint8_t *)maps + ehdr32->e_shoff);
		}
		print_program_headers_32(ehdr32, phdr32, shdr32, maps, is_big_endian);
	}

	munmap(maps, filesize);
	return EXIT_SUCCESS;
}
