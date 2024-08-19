#include "headers/philosophers.h"

int	main(int ac, char *av[])
{
	if (check_error(ac, av) == TRUE)
	{
		printf ("%sError!\n%s", RED, RESET);
		return (1);
	}
	return (0);
}
