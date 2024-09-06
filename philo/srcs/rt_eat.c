#include "../headers/philosophers.h"

void	ph_take_r_fork(t_philo *ph)
{
	t_philo	*left_ph;
	t_philo	*right_ph;

	left_ph = ph;
	right_ph = &ph->data->philosopher[ph->r_fork_id];
	wait_fork (right_ph);
	change_fork_state (right_ph, IN_USE);
	print_action (ph->id, "has taken a fork", ph->data);
	wait_fork (left_ph);
	change_fork_state (left_ph, IN_USE);
	print_action (ph->id, "has taken a fork", ph->data);
}

void	ph_take_l_fork(t_philo *ph)
{
	t_philo	*left_ph;
	t_philo	*right_ph;

	left_ph = ph;
	right_ph = &ph->data->philosopher[ph->r_fork_id];
	wait_fork (left_ph);
	change_fork_state (left_ph, IN_USE);
	print_action (ph->id, "has taken a fork", ph->data);
	wait_fork (right_ph);
	change_fork_state (right_ph, IN_USE);
	print_action (ph->id, "has taken a fork", ph->data);
}

void	ph_drop_fork(t_philo *ph)
{
	t_philo	*left_ph;
	t_philo	*right_ph;

	left_ph = ph;
	right_ph = &ph->data->philosopher[ph->r_fork_id];
	if (ph->id % 2 == 1)
	{
		change_fork_state (left_ph, FREE);
		change_fork_state (right_ph, FREE);
	}
	else
	{
		change_fork_state (right_ph, FREE);
		change_fork_state (left_ph, FREE);
	}
}

void	rt_eat(t_data *table, t_philo *ph)
{
	ph_take_fork (ph);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = TRUE;
	pthread_mutex_unlock (&table->check_lock);
	print_action (ph->id, "is eating", table);
	pthread_mutex_lock (&table->check_lock);
	ph->last_meal = ph_get_current_time ();
	ph->meal_eaten ++;
	pthread_mutex_unlock (&table->check_lock);
	ph_usleep (table->time_to_eat, ph->data);
	pthread_mutex_lock (&table->check_lock);
	ph->eating = FALSE;
	pthread_mutex_unlock (&table->check_lock);
	ph_drop_fork (ph);
}
