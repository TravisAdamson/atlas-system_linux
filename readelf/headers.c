#include "readelf.h"

void print_header_size_32(Elf32_Ehdr *e_hdr)
{
    unsigned int size = 0;
	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
    	size = __bswap_32(e_hdr->e_ehsize);
    else
        size = e_hdr->e_ehsize;
    printf("%u (bytes)\n", size);
}

void print_pheader_size_32(Elf32_Ehdr *e_hdr)
{
    unsigned int size = 0;
	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
    	size = __bswap_32(e_hdr->e_phentsize);
    else
        size = e_hdr->e_phentsize;
    printf("%u (bytes)\n", size);
}

void print_sheader_size_32(Elf32_Ehdr *e_hdr)
{
    unsigned int size = 0;
	if (e_hdr->e_ident[EI_DATA] == ELFDATA2MSB)
    	size = __bswap_32(e_hdr->e_shentsize);
    else
        size = e_hdr->e_shentsize;
    printf("%u (bytes)\n", size);
}
