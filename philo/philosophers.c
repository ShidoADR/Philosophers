#include "headers/philosophers.h"
#include "headers/struct.h"
#include <bits/types/struct_timeval.h>
#include <pthread.h>
#include <sys/time.h>

void	ph_init_philo(int ac, char *av[], t_philo *ph)
{
	int		i;

	ph->n_philosophers = ft_atol (av[1]);
	ph->time_to_die = ft_atol (av[2]);
	ph->time_to_eat = ft_atol (av[3]);
	ph->time_to_sleep = ft_atol(av[4]);
	ph->n_must_eat = ft_atol (av[5]);
	if (ac == 6)
		ph->n_must_eat = ft_atol (av[5]);
	i = 0;
	while (i < ph->n_philosophers)
	{
		ph->data[i].id = i + 1;
		ph->data[i].is_dead = FALSE;
		ph->data[i].meal_eaten = 0;
		ph->data[i].time_to_start = 0;
		pthread_mutex_init (&(ph->data[i].fork), NULL);
		i++;
	}
}

long long	ph_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	*philosophize(void *ph)
{
	t_philo	*data;

	data = (t_philo *)ph;
	return (NULL);
}

void	ph_mutex_destroy(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->n_philosophers)
	{
		pthread_mutex_destroy (&(ph->data[i].fork));
		i++;
	}
}

void	ph_routine(t_philo *ph)
{
	int	i;

	i = 0;
	while (i < ph->n_philosophers)
	{
		pthread_create (&(ph->thread[i]), NULL, philosophize, ph);
		i++;
	}
	i = 0;
	while (i < ph->n_philosophers)
	{
		pthread_join (ph->thread[i], NULL);
		i++;
	}
	ph_mutex_destroy (ph);
}

int	main(int ac, char *av[])
{
	t_philo	philosophers;

	if (check_error(ac, av) == TRUE)
	{
		printf ("%sError!\n%s", RED, RESET);
		return (1);
	}
	ph_init_philo (ac, av, &philosophers);
	ph_routine (&philosophers);
	return (0);
}
