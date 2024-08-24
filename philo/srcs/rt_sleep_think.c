#include "../headers/philosophers.h"

void	rt_think(t_data *table, t_philo *ph)
{
	print_action(ph->fork, "is thinking", table);
	ph_usleep (100);
}

void	rt_sleep(t_data *table, t_philo *ph)
{
	print_action(ph->fork, "is sleeping", table);
	ph_usleep (table->time_to_sleep);
}
