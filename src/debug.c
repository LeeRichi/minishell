#include <unistd.h>
#include <stdio.h>

void check_std_open(void)
{
	printf("stdread is a tty: %d\nstdwrite is a tty: %d\nstderr is a tty: %d\n", isatty(0), isatty(1), isatty(2));
}
