#include "../headers/philosophers.h"

void	ph_mutex_init(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_init (&(table->death_lock), NULL);
	pthread_mutex_init (&(table->write_lock), NULL);
	pthread_mutex_init (&(table->check_lock), NULL);
	while (i < table->n_philosophers)
	{
		pthread_mutex_init (&(table->philosopher[i].fork_lock), NULL);
		i++;
	}
}

void	ph_mutex_destroy(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy (&(table->death_lock));
	pthread_mutex_destroy (&(table->write_lock));
	pthread_mutex_destroy (&(table->check_lock));
	while (i < table->n_philosophers)
	{
		pthread_mutex_init (&(table->philosopher[i].fork_lock), NULL);
		i++;
	}
}
