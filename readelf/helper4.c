#include "1hreadelf.h"

void print_flag_key_64(void)
{
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)");
	printf(", l (large)\n");
	printf("  I (info), L (link order), G (group), ");
	printf("T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required) ");
	printf("o (OS specific), p (processor specific)\n");
}
