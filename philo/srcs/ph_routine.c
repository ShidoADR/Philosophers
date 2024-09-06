#include "../headers/philosophers.h"

t_bool	is_full(t_philo *ph)
{
	int	meal_eaten;

	if (ph->data->n_must_eat == -1)
		return (FALSE);
	pthread_mutex_lock (&ph->data->check_lock);
	meal_eaten = ph->meal_eaten;
	pthread_mutex_unlock (&ph->data->check_lock);
	if (meal_eaten >= ph->data->n_must_eat)
		return (TRUE);
	return (FALSE);
}

void	*philosophize(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2 == 0)
		usleep (500);
	pthread_mutex_lock (&ph->data->check_lock);
	ph->last_meal = ph_get_current_time();
	pthread_mutex_unlock (&ph->data->check_lock);
	while (dead_body_detected (ph->data) == FALSE)
	{
		rt_eat (ph->data, ph);
		rt_sleep (ph->data, ph);
		rt_think (ph->data, ph);
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

void	ph_routine(t_data *table)
{
	monitoring (table);
	start_routine (table);
	ph_join_thread (table);
	ph_mutex_destroy (table);
}
