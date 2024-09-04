#include "../headers/philosophers.h"
#include <pthread.h>

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

t_bool	fork_state(t_philo *ph)
{
	t_bool	status;

	pthread_mutex_lock (&ph->fork_lock);
	status = ph->fork;
	pthread_mutex_unlock (&ph->fork_lock);
	return (status);
}

void	change_fork_state(t_philo *ph, t_bool value)
{
	pthread_mutex_lock (&ph->fork_lock);
	ph->fork = value;
	pthread_mutex_unlock (&ph->fork_lock);
}

void	wait_fork(t_philo *ph)
{
	while (fork_state (ph) == IN_USE && dead_body_detected (ph->data) == FALSE)
		usleep (1);
}

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

void	ph_take_fork(t_philo *ph)
{
	if (ph->id % 2 == 1)
		ph_take_r_fork (ph);
	else
		ph_take_l_fork (ph);
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
