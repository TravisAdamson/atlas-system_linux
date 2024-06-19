#include "1hreadelf.h"

const char *flags_to_string(uint64_t flags)
{
	static char flag_str[16];
	int pos = 0;

	if (flags & SHF_WRITE)
		flag_str[pos++] = 'W';
	if (flags & SHF_ALLOC)
		flag_str[pos++] = 'A';
	if (flags & SHF_EXECINSTR)
		flag_str[pos++] = 'X';
	if (flags & SHF_MERGE)
		flag_str[pos++] = 'M';
	if (flags & SHF_STRINGS)
		flag_str[pos++] = 'S';
	if (flags & SHF_INFO_LINK)
		flag_str[pos++] = 'I';
	if (flags & SHF_LINK_ORDER)
		flag_str[pos++] = 'L';
	if (flags & SHF_GROUP)
		flag_str[pos++] = 'G';
	if (flags & SHF_TLS)
		flag_str[pos++] = 'T';
	if (flags & SHF_EXCLUDE)
		flag_str[pos++] = 'E';
	if (flags & SHF_MASKOS)
		flag_str[pos++] = 'o';
	if (flags & SHF_MASKPROC)
		flag_str[pos++] = 'p';
	if (flags & SHF_OS_NONCONFORMING)
		flag_str[pos++] = 'O';
	flag_str[pos] = '\0';

	return (flag_str);
}