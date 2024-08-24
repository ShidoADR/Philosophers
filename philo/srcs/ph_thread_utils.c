#include "../headers/philosophers.h"

t_bool	dead_body_detected(t_data *table)
{
	pthread_mutex_lock (&table->death_lock);
	if (table->is_dead == TRUE)
	{
		pthread_mutex_unlock (&table->death_lock);
		return (TRUE);
	}
	pthread_mutex_unlock (&table->death_lock);
	return (FALSE);
}

t_bool	is_deceased(t_data *table, t_philo *ph)
{
	long long	time_remaining;

	pthread_mutex_lock (&table->check_lock);
	time_remaining = ph_get_current_time() - ph->last_meal;
	if (time_remaining >= table->time_to_die && ph->eating == FALSE)
	{
		pthread_mutex_unlock (&table->check_lock);
		return (TRUE);
	}
	pthread_mutex_unlock (&table->check_lock);
	return (FALSE);
}

void	ph_join_thread(t_data *table)
{
	int	i;

	pthread_join (table->monitor, NULL);
	i = 0;
	while (i < table->n_philosophers)
	{
		pthread_join (table->philosopher[i].thread, NULL);
		i++;
	}
}
