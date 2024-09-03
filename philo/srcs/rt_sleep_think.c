#include "../headers/philosophers.h"

void	rt_think(t_data *table, t_philo *ph)
{
	int	sleep;

	print_action(ph->id, "is thinking", table);
	if (table->n_philosophers % 2 == 1)
	{
		sleep = (table->time_to_eat * 2) - table->time_to_sleep;
		ph_usleep (sleep, table);
	}
	else if (table->n_philosophers > 100)
	{
		sleep = 1;
		ph_usleep (sleep, table);
	}
}

void	rt_sleep(t_data *table, t_philo *ph)
{
	print_action(ph->id, "is sleeping", table);
	ph_usleep (table->time_to_sleep, table);
}
