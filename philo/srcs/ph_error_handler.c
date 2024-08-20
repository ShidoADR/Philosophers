#include "../headers/philosophers.h"

t_bool	is_numeric(char *number)
{
	int	i;

	if (!number)
		return (FALSE);
	i = 0;
	while (number[i] != '\0')
	{
		if (number[i] < '0' || number[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	check_error(int ac, char *av[])
{
	int	i;

	if (ac < 5 || ac > 6)
		return (TRUE);
	i = 1;
	while (av[i] != NULL)
	{
		if (is_numeric(av[i]) == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
