#include "readelf.h"

void print_offset_32(Elf32_Ehdr *e_hdr)
{
    Elf32_Off sect_off = e_hdr->e_shoff;
    printf(" %lu (bytes into file)\n", sect_off);
}

void print_offset_64(Elf64_Ehdr *e_hdr)
{
    Elf64_Off sect_off =  e_hdr->e_shoff;
    printf(" %lu (bytes into file)\n", sect_off);
}