#include "readelf.h"

void print_osabi_64(Elf64_Ehdr *e_hdr)
{
	switch (e_hdr->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("HP-UX ABI\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("Linux ABI\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		case ELFOSABI_IRIX:
			printf("IRIX ABI\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD ABI\n");
			break;
		case ELFOSABI_TRU64:
			printf("TRU64 UNIX ABI\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM Architecture ABI\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Stand-alone (embedded) ABI");
			break;
		default:
			printf("UNIX - System V\n");
			break;
	};
}

void print_osabi_32(Elf32_Ehdr *e_hdr)
{
	switch (e_hdr->e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("HP-UX ABI\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("Linux ABI\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		case ELFOSABI_IRIX:
			printf("IRIX ABI\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD ABI\n");
			break;
		case ELFOSABI_TRU64:
			printf("TRU64 UNIX ABI\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM Architecture ABI\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Stand-alone (embedded) ABI");
			break;
		case '6':
			printf("<unknown: 53>\n");
			break;
		default:
			printf("UNIX - System V\n");
			break;
	};
}
