#include "../headers/philosophers.h"

t_error_flag	is_valid_arguments(int ac, char *av[], t_data *table)
{
	if (ac < 5 || ac > 6)
		return (ARG_NUMBER);
	if (check_error (av) == TRUE)
		return (INPUT_VALUE);
	if (table->n_philosophers <= 0 || table->n_philosophers > THREAD_MAX)
		return (PHILO_NUMBER);
	if (table->time_to_die < 0)
		return (ARG_VALUE);
	if (table->time_to_eat < 0)
		return (ARG_VALUE);
	if (table->time_to_sleep < 0)
		return (ARG_VALUE);
	if (ac == 6 && table->n_philosophers <= 0)
		return (ARG_VALUE);
	return (TRUE);
}

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

t_bool	check_error(char *av[])
{
	int	i;

	i = 1;
	while (av[i] != NULL)
	{
		if (is_numeric (av[i]) == FALSE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
