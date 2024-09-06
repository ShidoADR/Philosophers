#include "../headers/philosophers.h"

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
	while (fork_state (ph) == IN_USE)
		usleep (1);
}

void	ph_take_fork(t_philo *ph)
{
	if (ph->id % 2 == 1)
		ph_take_r_fork (ph);
	else
		ph_take_l_fork (ph);
}
