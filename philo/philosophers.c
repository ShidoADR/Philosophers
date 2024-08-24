#include "headers/philosophers.h"

int	main(int ac, char *av[])
{
	t_data	table;

	if (ph_init_philo (ac, av, &table) == FALSE)
		return (1);
	ph_routine (&table);
	return (0);
}
