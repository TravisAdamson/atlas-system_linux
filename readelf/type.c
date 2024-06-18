#include "readelf.h"

void print_type_64(Elf64_Ehdr *e_hdr)
{
	switch (e_hdr->e_type)
	{
		case ET_REL:
			printf("REL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("DYN (Shared object file)\n");
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
	unsigned int new_type;
	
	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
		new_type = __bswap_16(e_hdr->e_type);
	else
		new_type = e_hdr->e_type;
	switch (new_type)
	{
		case ET_REL:
			printf("REL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("DYN (Shared object file)\n");
			break;
		case ET_CORE:
			printf("A core file\n");
			break;
		default:
			printf("An unknown file\n");
			break;
	};
}
