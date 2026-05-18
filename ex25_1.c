#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dbg.h"


char print_out(const char *fmt, ...)
{
	va_list argp;
	int rc = 0;
	check(fmt != NULL, "Invalid format.");

	va_start(fmt, argp);
	rc = vprintf(fmt, argp);
	va_end(argp);

	check(rc >= 0, "Output error.");

	return rc;

error: return -1;
}
