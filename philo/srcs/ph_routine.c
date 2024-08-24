#include "../headers/philosophers.h"

void	*philosophize(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	while (dead_body_detected (ph->data) == FALSE)
	{
		rt_eat(ph->data, ph);
		rt_sleep(ph->data, ph);
		rt_think(ph->data, ph);
	}
	return (NULL);
}

void	start_routine(t_data *t)
{
	int		i;
	t_philo	*ph;

	i = 0;
	while (i < t->n_philosophers)
	{
		ph = &t->philosopher[i];
		pthread_create (&(ph->thread), NULL, philosophize, &(*ph));
		i ++;
	}
}

void	get_start_time(t_data *table)
{
	int	i;

	i = 0;
	while (i < table->n_philosophers)
	{
		ph_usleep (1);
		i++;
	}
	table->time_to_start = ph_get_current_time ();
}

void	ph_routine(t_data *table)
{
	monitoring (table);
	get_start_time (table);
	start_routine (table);
	ph_join_thread (table);
	ph_mutex_destroy (table);
}
