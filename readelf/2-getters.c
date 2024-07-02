#include "2hreadelf.h"

const char *get_segment_type(uint32_t p_type)
{
	switch (p_type)
	{
	case PT_NULL:
		return ("NULL");
	case PT_LOAD:
		return ("LOAD");
	case PT_DYNAMIC:
		return ("DYNAMIC");
	case PT_INTERP:
		return ("INTERP");
	case PT_NOTE:
		return ("NOTE");
	case PT_SHLIB:
		return ("SHLIB");
	case PT_PHDR:
		return ("PHDR");
	case PT_TLS:
		return ("TLS");
	case PT_GNU_EH_FRAME:
		return ("GNU_EH_FRAME");
	case PT_GNU_STACK:
		return ("GNU_STACK");
	case PT_GNU_RELRO:
		return ("GNU_RELRO");
	default:
		return ("LOOS+464e550");
	}
}

const char *get_file_type(uint16_t e_type)
{
	switch (e_type)
	{
	case ET_NONE:
		return ("NONE (No file type)");
	case ET_REL:
		return ("REL (Relocatable file)");
	case ET_EXEC:
		return ("EXEC (Executable file)");
	case ET_DYN:
		return ("DYN (Shared object file)");
	case ET_CORE:
		return ("CORE (Core file)");
	default:
		return ("UNKNOWN");
	}
}
