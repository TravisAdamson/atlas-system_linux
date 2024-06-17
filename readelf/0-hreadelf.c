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
	int fd = 0, flag_64 = 0;
	void *map_head = NULL;
	Elf64_Ehdr *e_hdr_64 = NULL;
	Elf32_Ehdr *e_hdr_32 = NULL;

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
	e_hdr_32 = (Elf32_Ehdr *)map_head;
	if (e_hdr_32->e_ident[EI_CLASS] == ELFCLASS64)
		e_hdr_64 = (Elf64_Ehdr *)map_head, flag_64 = 1;
	if (e_hdr_32->e_ident[EI_MAG0] != ELFMAG0 ||
		e_hdr_32->e_ident[EI_MAG1] != ELFMAG1 ||
		e_hdr_32->e_ident[EI_MAG2] != ELFMAG2 ||
		e_hdr_32->e_ident[EI_MAG3] != ELFMAG3) {
		fprintf(stderr, "Not a valid ELF file\n");
		munmap(map_head, file_stat.st_size);
		close(fd);
		exit(EXIT_FAILURE);
	}
	if (flag_64)
		print_head_64(e_hdr_64);
	else
		print_head_32(e_hdr_32);
	munmap(map_head, file_stat.st_size), close(fd);
	return (0);
}

/**
 * print_head_32 - Print the elf header
 * @e_head: mapped header
*/

void print_head_32(Elf32_Ehdr *e_hdr)
{
	int i = 0;

	printf("ELF Header:\n");
	printf(" Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", e_hdr->e_ident[i]);
	printf("\n");
	printf(" %-35s%u\n", "Class:", e_hdr->e_ident[EI_CLASS]);
	printf(" %-35s%u\n", "Data:", e_hdr->e_ident[EI_DATA]);
	printf(" %-35s%u\n", "Version:", e_hdr->e_ident[EI_VERSION]);
	printf(" %-35s%u\n", "OS/ABI:", e_hdr->e_ident[EI_OSABI]);
	printf(" %-35s%u\n", "ABI Ver:", e_hdr->e_ident[EI_ABIVERSION]);
	printf(" %-35s%u\n", "Type:", e_hdr->e_type);
	printf(" %-35s%u\n", "Machine:", e_hdr->e_machine);
	printf(" %-35s%x\n", "Version:", e_hdr->e_version);
	printf(" %-35s%x\n", "Entry point address:", e_hdr->e_entry);
	printf(" %-35s%x\n", "Start of program headers:", e_hdr->e_phoff);
	printf(" %-35s%x\n", "Start of section headers:", e_hdr->e_shoff);
	printf(" %-35s%x\n", "Flags:", e_hdr->e_flags);
	printf(" %-35s%u\n", "Size of this header:", e_hdr->e_ehsize);
	printf(" %-35s%u\n", "Size of program headers:", e_hdr->e_phentsize);
	printf(" %-35s%u\n", "Number of program headers:", e_hdr->e_phnum);
	printf(" %-35s%u\n", "Size of section headers:", e_hdr->e_shentsize);
	printf(" %-35s%u\n", "Number of section headers:", e_hdr->e_shnum);
	printf(" %-35s%u\n", "Section header string table index:", e_hdr->e_shstrndx);
}

/**
 * print_head_64 - Print the elf header
 * @e_head: mapped header
*/

void print_head_64(Elf64_Ehdr *e_hdr)
{
	int i = 0;

	printf("ELF Header:\n");
	printf(" Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", e_hdr->e_ident[i]);
	printf("\n");
	printf(" %-35s%u\n", "Class:", e_hdr->e_ident[EI_CLASS]);
	printf(" %-35s%u\n", "Data:", e_hdr->e_ident[EI_DATA]);
	printf(" %-35s%u\n", "Version:", e_hdr->e_ident[EI_VERSION]);
	printf(" %-35s%u\n", "OS/ABI:", e_hdr->e_ident[EI_OSABI]);
	printf(" %-35s%u\n", "ABI Ver:", e_hdr->e_ident[EI_ABIVERSION]);
	printf(" %-35s%u\n", "Type:", e_hdr->e_type);
	printf(" %-35s%u\n", "Machine:", e_hdr->e_machine);
	printf(" %-35s%x\n", "Version:", e_hdr->e_version);
	printf(" %-35s%lx\n", "Entry point address:", e_hdr->e_entry);
	printf(" %-35s%lx\n", "Start of program headers:", e_hdr->e_phoff);
	printf(" %-35s%lx\n", "Start of section headers:", e_hdr->e_shoff);
	printf(" %-35s%x\n", "Flags:", e_hdr->e_flags);
	printf(" %-35s%u\n", "Size of this header:", e_hdr->e_ehsize);
	printf(" %-35s%u\n", "Size of program headers:", e_hdr->e_phentsize);
	printf(" %-35s%u\n", "Number of program headers:", e_hdr->e_phnum);
	printf(" %-35s%u\n", "Size of section headers:", e_hdr->e_shentsize);
	printf(" %-35s%u\n", "Number of section headers:", e_hdr->e_shnum);
	printf(" %-35s%u\n", "Section header string table index:", e_hdr->e_shstrndx);
}
