#include "2hreadelf.h"

void swap_endianess_32(Elf32_Ehdr *ehdr,
					Elf32_Phdr *phdr,
					Elf32_Shdr *shdr,
					int phnum)
{
	int i;
	int snum = bswap_16(ehdr->e_shnum);

	for (i = 0; i < phnum; i++)
	{
		phdr[i].p_type = bswap_32(phdr[i].p_type);
		phdr[i].p_offset = bswap_32(phdr[i].p_offset);
		phdr[i].p_vaddr = bswap_32(phdr[i].p_vaddr);
		phdr[i].p_paddr = bswap_32(phdr[i].p_paddr);
		phdr[i].p_filesz = bswap_32(phdr[i].p_filesz);
		phdr[i].p_memsz = bswap_32(phdr[i].p_memsz);
		phdr[i].p_flags = bswap_32(phdr[i].p_flags);
		phdr[i].p_align = bswap_32(phdr[i].p_align);
	}
	for (i = 0; i < snum; i++)
	{
		shdr[i].sh_name = bswap_32(shdr[i].sh_name);
		shdr[i].sh_type = bswap_32(shdr[i].sh_type);
		shdr[i].sh_flags = bswap_32(shdr[i].sh_flags);
		shdr[i].sh_addr = bswap_32(shdr[i].sh_addr);
		shdr[i].sh_offset = bswap_32(shdr[i].sh_offset);
		shdr[i].sh_size = bswap_32(shdr[i].sh_size);
		shdr[i].sh_link = bswap_32(shdr[i].sh_link);
		shdr[i].sh_info = bswap_32(shdr[i].sh_info);
		shdr[i].sh_addralign = bswap_32(shdr[i].sh_addralign);
		shdr[i].sh_entsize = bswap_32(shdr[i].sh_entsize);
	}
	ehdr->e_type = bswap_16(ehdr->e_type);
	ehdr->e_machine = bswap_16(ehdr->e_machine);
	ehdr->e_version = bswap_32(ehdr->e_version);
	ehdr->e_entry = bswap_32(ehdr->e_entry);
	ehdr->e_phoff = bswap_32(ehdr->e_phoff);
	ehdr->e_shoff = bswap_32(ehdr->e_shoff);
	ehdr->e_flags = bswap_32(ehdr->e_flags);
	ehdr->e_ehsize = bswap_16(ehdr->e_ehsize);
	ehdr->e_phentsize = bswap_16(ehdr->e_phentsize);
	ehdr->e_phnum = bswap_16(ehdr->e_phnum);
	ehdr->e_shentsize = bswap_16(ehdr->e_shentsize);
	ehdr->e_shnum = bswap_16(ehdr->e_shnum);
	ehdr->e_shstrndx = bswap_16(ehdr->e_shstrndx);
}

void swap_endianess_64(Elf64_Phdr *phdr, int phnum)
{
	int i;

	for (i = 0; i < phnum; i++)
	{
		phdr[i].p_type = __bswap_32(phdr[i].p_type);
		phdr[i].p_offset = __bswap_64(phdr[i].p_offset);
		phdr[i].p_vaddr = __bswap_64(phdr[i].p_vaddr);
		phdr[i].p_paddr = __bswap_64(phdr[i].p_paddr);
		phdr[i].p_filesz = __bswap_64(phdr[i].p_filesz);
		phdr[i].p_memsz = __bswap_64(phdr[i].p_memsz);
		phdr[i].p_flags = __bswap_32(phdr[i].p_flags);
		phdr[i].p_align = __bswap_64(phdr[i].p_align);
	}
}
