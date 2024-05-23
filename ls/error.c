#include "hls.h"

/**
 * print_error - Print error message based on errno
 * @prog: Program making the call
 * @file: File being called
 * @errno: The errno being returned from call
*/

void print_error(const char *prog, const char *file_name, int error)
{
	if (error == 2)
		fprintf(
			stderr,
			"%s: cannot access %s: No such file or directory\n", prog, file_name
		);
	else if (error == 13)
		fprintf(
			stderr,
			"%s: cannot open directory %s: Permission denied\n", prog, file_name
		);
}