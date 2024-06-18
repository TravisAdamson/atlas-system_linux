#include "readelf.h"

void print_type_64(Elf64_Ehdr *e_hdr)
{
	switch (e_hdr->e_type)
	{
		case ET_REL:
			printf("A relocatable file\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("A shared object\n");
			break;
		case ET_CORE:
			printf("A core file\n");
			break;
		default:
			printf("An unknown file\n");
			break;
	};
}

void print_type_32(Elf32_Ehdr *e_hdr)
{
	switch (e_hdr->e_type)
	{
		case ET_REL:
			printf("A relocatable file\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("A shared object\n");
			break;
		case ET_CORE:
			printf("A core file\n");
			break;
		default:
			printf("An unknown file\n");
			break;
	};
}
