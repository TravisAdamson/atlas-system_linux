#include "readelf.h"

/**
 * main - The primary function
 * @argc: Number of arguements given
 * @argv: Array of arguments
 * Return: 1 for failure, 0 for success
*/

int main(int argc, char **argv)
{
	struct stat file_stat;
	const char *f_name = argv[1];
	int fd = 0;
	void *map_head = NULL;
	Elf64_Ehdr *e_hdr = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	fd = open(f_name, O_RDONLY);
	if (fd == -1)
		perror("open"), exit(EXIT_FAILURE);

	if (fstat(fd, &file_stat) == -1)
		perror("fstat"), close(fd), exit(EXIT_FAILURE);

	map_head = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

	if (map_head == MAP_FAILED)
		perror("mmap"), close(fd), exit(EXIT_FAILURE);

	e_hdr = (Elf64_Ehdr *)map_head;

	if (e_hdr->e_ident[EI_MAG0] != ELFMAG0 ||
		e_hdr->e_ident[EI_MAG1] != ELFMAG1 ||
		e_hdr->e_ident[EI_MAG2] != ELFMAG2 ||
		e_hdr->e_ident[EI_MAG3] != ELFMAG3) {
		fprintf(stderr, "Not a valid ELF file\n");
		munmap(map_head, file_stat.st_size);
		close(fd);
		exit(EXIT_FAILURE);
	}

	printf("ELF Header:\n");
	printf("  Magic: %-25s\n", e_hdr->e_ident);
	printf("  Class: %-25u\n", e_hdr->e_ident[EI_CLASS]);
	printf("  Data: %-25u\n", e_hdr->e_ident[EI_DATA]);
	printf("  Version: %-25u\n", e_hdr->e_ident[EI_VERSION]);
	printf("  OS/ABI: %-25u\n", e_hdr->e_ident[EI_OSABI]);
	printf("  ABI Ver: %-25u\n", e_hdr->e_ident[EI_ABIVERSION]);
	printf("  Type: %-25u\n", e_hdr->e_type);
	printf("  Machine: %-25u\n", e_hdr->e_machine);
	printf("  Version: %-25x\n", e_hdr->e_version);
	printf("  Entry point address: %-25lx\n", e_hdr->e_entry);
	printf("  Start of program headers: %-25lu\n", e_hdr->e_phoff);
	printf("  Start of section headers: %-25lu\n", e_hdr->e_shoff);
	printf("  Flags: %-25x\n", e_hdr->e_flags);
	printf("  Size of this header: %-25u\n", e_hdr->e_ehsize);
	printf("  Size of program headers: %-25u\n", e_hdr->e_phentsize);
	printf("  Number of program headers: %-25u\n", e_hdr->e_phnum);
	printf("  Size of section headers: %-25u\n", e_hdr->e_shentsize);
	printf("  Number of section headers: %-25u\n", e_hdr->e_shnum);
	printf("  Section header string table index: %-25u\n", e_hdr->e_shstrndx);

	munmap(map_head, file_stat.st_size);
	close(fd);

	return (0);
}