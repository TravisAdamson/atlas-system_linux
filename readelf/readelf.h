#ifndef __readelf_h__
#define __readelf_h__

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

void print_head(Elf64_Ehdr *e_hdr);

#endif
