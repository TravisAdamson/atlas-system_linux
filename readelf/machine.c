#include "readelf.h"

void print_machine_64(Elf64_Ehdr *e_hdr)
{
	switch (e_hdr->e_machine)
	{
		case EM_M32:
			printf("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			printf("Sun Microsystems SPARC\n");
			break;
		case EM_386:
			printf("Intel 80386\n");
			break;
		case EM_68K:
			printf("Motorola 68000\n");
			break;
		case EM_88K:
			printf("Motorola 88000\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS RS3000 (big-endian only)\n");
			break;
		case EM_PARISC:
			printf("HP/PA\n");
			break;
		case EM_SPARC32PLUS:
			printf("SPARC with enhanced instruction set\n");
			break;
		case EM_PPC:
			printf("PowerPC\n");
			break;
		default:
			print_machine_64_2(e_hdr);
	};
}

void print_machine_64_2(Elf64_Ehdr *e_hdr)
{
	switch (e_hdr->e_machine)
	{
		case EM_PPC64:
			printf("PowerPC 64-bit\n");
			break;
		case EM_S390:
			printf("IBM S/390\n");
			break;
		case EM_ARM:
			printf("Advanced RISC Machines\n");
			break;
		case EM_SH:
			printf("Renesas SuperH\n");
			break;
		case EM_SPARCV9:
			printf("SPARC v9 64-bit\n");
			break;
		case EM_IA_64:
			printf("Intel Itanium\n");
			break;
		case EM_X86_64:
			printf("Advanced Micro Devices x86-64\n");
			break;
		case EM_VAX:
			printf("DEC Vax\n");
			break;
		default:
			printf("An unknown machine\n");
			break;
	};
}

void print_machine_32(Elf32_Ehdr *e_hdr)
{
	switch (e_hdr->e_machine)
	{
		case EM_M32:
			printf("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			printf("Sun Microsystems SPARC\n");
			break;
		case EM_386:
			printf("Intel 80386\n");
			break;
		case EM_68K:
			printf("Motorola 68000\n");
			break;
		case EM_88K:
			printf("Motorola 88000\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS RS3000 (big-endian only)\n");
			break;
		case EM_PARISC:
			printf("HP/PA\n");
			break;
		case EM_SPARC32PLUS:
			printf("SPARC with enhanced instruction set\n");
			break;
		case EM_PPC:
			printf("PowerPC\n");
			break;
		default:
			print_machine_32_2(e_hdr);
	};
}

void print_machine_32_2(Elf32_Ehdr *e_hdr)
{
	switch (e_hdr->e_machine)
	{
		case EM_PPC64:
			printf("PowerPC 64-bit\n");
			break;
		case EM_S390:
			printf("IBM S/390\n");
			break;
		case EM_ARM:
			printf("Advanced RISC Machines\n");
			break;
		case EM_SH:
			printf("Renesas SuperH\n");
			break;
		case EM_SPARCV9:
			printf("SPARC v9 64-bit\n");
			break;
		case EM_IA_64:
			printf("Intel Itanium\n");
			break;
		case EM_X86_64:
			printf("Advanced Micro Devices x86-64\n");
			break;
		case EM_VAX:
			printf("DEC Vax\n");
			break;
		default:
			printf("An unknown machine\n");
			break;
	};
}
