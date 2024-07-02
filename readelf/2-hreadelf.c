#include "2hreadelf.h"

int main(int argc, char **argv)
{
	const char *filename;
	int fd, is_64_bit, is_big_endian, filesize;
	struct stat st;
	void *maps;
	Elf64_Ehdr *ehdr;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <elf-file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	filename = argv[1];
	fd = open(filename, O_RDONLY);
	filesize = fstat(fd, &st);
	maps = mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (fd == -1 || filesize == -1 || maps == MAP_FAILED)
	{
		perror("Failed to map ELF file");
		close(fd);
		return (EXIT_FAILURE);
	}
	close(fd);
	ehdr = (Elf64_Ehdr *)maps;
	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0)
	{
		fprintf(stderr, "Not a valid ELF file\n");
		munmap(maps, st.st_size);
		return (EXIT_FAILURE);
	}
	is_big_endian = (ehdr->e_ident[EI_DATA] == ELFDATA2MSB);
	is_64_bit = (ehdr->e_ident[EI_CLASS] == ELFCLASS64);
	setup_printing(is_big_endian, is_64_bit, ehdr, maps);
	munmap(maps, st.st_size);
	return (EXIT_SUCCESS);
}

void setup_printing(int is_big_endian, int is_64_bit, Elf64_Ehdr *ehdr,
					const char *maps)
{
	Elf32_Ehdr *ehdr32;
	Elf64_Phdr *phdr;
	Elf32_Phdr *phdr32;
	Elf64_Shdr *shdr64;
	Elf32_Shdr *shdr32;

	if (is_64_bit)
	{
		phdr = (Elf64_Phdr *)((uint8_t *)maps + ehdr->e_phoff);
		shdr64 = (Elf64_Shdr *)((uint8_t *)maps + ehdr->e_shoff);
		print_program_headers_64(ehdr, phdr, shdr64, maps, is_big_endian);
	}
	else
	{
		ehdr32 = (Elf32_Ehdr *)ehdr;
		phdr32 = (Elf32_Phdr *)((uint8_t *)maps +
			(is_big_endian ? bswap_32(ehdr32->e_phoff) : ehdr32->e_phoff));
		shdr32 = (Elf32_Shdr *)((uint8_t *)maps +
			(is_big_endian ? bswap_32(ehdr32->e_shoff) : ehdr32->e_shoff));
		print_program_headers_32(ehdr32, phdr32, shdr32, maps, is_big_endian);
	}
}
