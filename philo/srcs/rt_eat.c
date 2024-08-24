#include "../headers/philosophers.h"

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
		return ;
	ph_take_fork(ph);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = TRUE;
	pthread_mutex_unlock (&table->check_lock);
	print_action (ph->fork, "is eating", table);
	pthread_mutex_lock (&table->check_lock);
	ph->last_meal = ph_get_current_time ();
	ph->meal_eaten ++;
	pthread_mutex_unlock (&table->check_lock);
	ph_usleep (table->time_to_eat);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = FALSE;
	pthread_mutex_unlock (&table->check_lock);
	ph_drop_fork(ph);
}
