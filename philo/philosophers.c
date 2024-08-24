#include "headers/philosophers.h"

long long	ph_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	print_action(short id, char *message, t_data *table)
{
	t_bool		status;
	long long	timestamp;

	usleep(10);
	pthread_mutex_lock (&table->death_lock);
	status = table->is_dead;
	pthread_mutex_unlock (&table->death_lock);
	pthread_mutex_lock (&table->write_lock);
	timestamp = ph_get_current_time () - table->time_to_start;
	if (status == FALSE)
	{
		printf ("%s%lld%s", YELLOW, timestamp, RESET);
		printf (" %hd", id);
		printf (" %s%s%s\n", GREEN, message, RESET);
	}
	pthread_mutex_unlock (&table->write_lock);
}

void	print_death(short id, t_data *table)
{
	long long	timestamp;

	pthread_mutex_lock (&table->write_lock);
	timestamp = ph_get_current_time () - table->time_to_start;
	printf ("%s", RED);
	printf ("%lld %hd died\n", timestamp, id);
	printf ("%s", RESET);
	pthread_mutex_unlock (&table->write_lock);
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

t_bool	check_death(t_data *table)
{
	short	i;
	short	n;

	i = 0;
	n = table->n_philosophers;
	while (i < n)
	{
		if (is_deceased(table, &table->philosopher[i]) == TRUE)
		{
			pthread_mutex_lock (&table->death_lock);
			print_death (table->philosopher[i].fork, table);
			table->is_dead = TRUE;
			pthread_mutex_unlock (&table->death_lock);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

t_bool	check_eaten(t_data *table)
{
	int		count_finish_eating;
	short	i;

	i = 0;
	count_finish_eating = 0;
	if (table->n_must_eat == -1)
		return (FALSE);
	while (i < table->n_philosophers)
	{
		pthread_mutex_lock(&table->check_lock);
		if (table->philosopher[i].meal_eaten == table->n_must_eat)
			count_finish_eating ++;
		pthread_mutex_unlock(&table->check_lock);
		i++;
	}
	if (count_finish_eating == table->n_philosophers)
	{
		pthread_mutex_lock (&table->death_lock);
		table->is_dead = TRUE;
		pthread_mutex_unlock (&table->death_lock);
		return (TRUE);
	}
	return (FALSE);
}

void	ph_mutex_init(t_data *table)
{
	short	i;

	i = 0;
	pthread_mutex_init(&(table->death_lock), NULL);
	pthread_mutex_init(&(table->write_lock), NULL);
	pthread_mutex_init(&(table->check_lock), NULL);
	while (i < table->n_philosophers)
	{
		pthread_mutex_init(&(table->fork_lock[i]), NULL);
		i++;
	}
}

t_error_flag	is_valid_arguments(int ac, char *av[], t_data *table)
{
	if (check_error (ac, av) == TRUE)
		return (INPUT_VALUE);
	if (table->n_philosophers <= 0 || table->n_philosophers > 200)
		return (PHILO_NUMBER);
	if (table->time_to_die <= 0)
		return (ARG_VALUE);
	if (table->time_to_eat <= 0)
		return (ARG_VALUE);
	if (table->time_to_sleep <= 0)
		return (ARG_VALUE);
	if (ac == 6 && table->n_philosophers <= 0)
		return (ARG_VALUE);
	return (TRUE);
}

void	ph_init_data(int ac, char *av[], t_data *table)
{
	table->n_philosophers = ft_atol (av[1]);
	table->time_to_die = ft_atol (av[2]);
	table->time_to_eat = ft_atol (av[3]);
	table->time_to_sleep = ft_atol (av[4]);
	table->n_must_eat = -1;
	table->time_to_start = ph_get_current_time();
	table->is_dead = FALSE;
	table->is_all_eaten = FALSE;
	if (ac == 6)
		table->n_must_eat = ft_atol (av[5]);
}

void	print_error(t_error_flag flag)
{
	if (flag == PHILO_NUMBER)
	{
		printf ("%sError : ", RED);
		printf ("number of philosophers must be in range of 1 and 200");
		printf ("\n%s", RESET);
	}
	if (flag == ARG_VALUE)
	{
		printf ("%sError : ", RED);
		printf ("bad arguments value");
		printf ("\n%s", RESET);
	}
	if (flag == INPUT_VALUE)
	{
		printf ("%sError : ", RED);
		printf ("bad input (digit value only)");
		printf ("\n%s", RESET);
	}
}

t_bool	ph_init_philo(int ac, char *av[], t_data *table)
{
	int		i;
	short	n;

	ph_init_data(ac, av, table);
	if (is_valid_arguments (ac, av, table) <= 0)
	{
		print_error (is_valid_arguments (ac, av, table));
		return (FALSE);
	}
	i = 0;
	n = table->n_philosophers;
	while (i < n)
	{
		table->philosopher[i].data = table;
		table->philosopher[i].fork = i + 1;
		table->philosopher[i].last_meal = table->time_to_start;
		table->philosopher[i].meal_eaten = 0;
		table->philosopher[i].l_fork_id = i;
		table->philosopher[i].r_fork_id = (i + 1) % n;
		table->philosopher[i].eating = FALSE;
		i++;
	}
	ph_mutex_init(table);
	return (TRUE);
}

void	ph_usleep(long long time)
{
	long long	start_time;

	start_time = ph_get_current_time ();
	while ((ph_get_current_time() - start_time) < time)
		usleep (100);
}

void	rt_think(t_data *table, t_philo *ph)
{
	print_action(ph->fork, "is thinking", table);
	ph_usleep (100);
}

void	rt_sleep(t_data *table, t_philo *ph)
{
	print_action(ph->fork, "is sleeping", table);
	ph_usleep (table->time_to_sleep);
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

void	ph_mutex_destroy(t_data *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&(table->death_lock));
	pthread_mutex_destroy(&(table->write_lock));
	pthread_mutex_destroy(&(table->check_lock));
	while (i < table->n_philosophers)
	{
		pthread_mutex_destroy (&(table->fork_lock[i]));
		i++;
	}
}

void	*observe(void *data)
{
	t_data		*table;
	long long	counter;

	table = (t_data *)data;
	counter = 0;
	while (check_death (table) == FALSE && check_eaten (table) == FALSE)
		counter ++;
	return (NULL);
}

void	monitoring(t_data *table)
{
	pthread_create(&(table->monitor), NULL, observe, table);
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

void	ph_routine(t_data *table)
{
	monitoring (table);
	get_start_time (table);
	start_routine (table);
	ph_join_thread (table);
	ph_mutex_destroy (table);
}

int	main(int ac, char *av[])
{
	t_data	table;

	if (ph_init_philo (ac, av, &table) == FALSE)
		return (1);
	ph_routine (&table);
	return (0);
}
