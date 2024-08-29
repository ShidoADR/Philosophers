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

void	ph_take_fork(t_philo *ph)
{
	if (ph->fork % 2 != 0)
	{
		pthread_mutex_lock (&ph->data->fork_lock[ph->r_fork_id]);
		print_action (ph->fork, "has taken a fork", ph->data);
		pthread_mutex_lock (&ph->data->fork_lock[ph->l_fork_id]);
		print_action (ph->fork, "has taken a fork", ph->data);
	}
	else
	{
		pthread_mutex_lock (&ph->data->fork_lock[ph->l_fork_id]);
		print_action (ph->fork, "has taken a fork", ph->data);
		pthread_mutex_lock (&ph->data->fork_lock[ph->r_fork_id]);
		print_action (ph->fork, "has taken a fork", ph->data);
	}
}

void	ph_drop_fork(t_philo *ph)
{
	if (ph->fork % 2 == 0)
	{
		pthread_mutex_unlock (&ph->data->fork_lock[ph->r_fork_id]);
		pthread_mutex_unlock (&ph->data->fork_lock[ph->l_fork_id]);
	}
	else
	{
		pthread_mutex_unlock (&ph->data->fork_lock[ph->l_fork_id]);
		pthread_mutex_unlock (&ph->data->fork_lock[ph->r_fork_id]);
	}
}

void	rt_eat(t_data *table, t_philo *ph)
{
	if (ph->data->n_philosophers == 1)
	{
		pthread_mutex_lock (&ph->data->fork_lock[ph->l_fork_id]);
		print_action (ph->fork, "has taken a fork", ph->data);
		ph_usleep (table->time_to_die, ph->data);
		pthread_mutex_unlock (&ph->data->fork_lock[ph->l_fork_id]);
		return ;
	}
	ph_take_fork(ph);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = TRUE;
	pthread_mutex_unlock (&table->check_lock);
	print_action (ph->fork, "is eating", table);
	pthread_mutex_lock (&table->check_lock);
	ph->last_meal = ph_get_current_time ();
	ph->meal_eaten ++;
	pthread_mutex_unlock (&table->check_lock);
	ph_usleep (table->time_to_eat, ph->data);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = FALSE;
	pthread_mutex_unlock (&table->check_lock);
	ph_drop_fork(ph);
}
