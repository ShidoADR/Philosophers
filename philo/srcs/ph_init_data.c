#include "../headers/philosophers.h"

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

t_bool	ph_init_philo(int ac, char *av[], t_data *table)
{
	int	i;
	int	n;

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
		table->philosopher[i].fork = FREE;
		table->philosopher[i].id = i + 1;
		table->philosopher[i].last_meal = table->time_to_start;
		table->philosopher[i].meal_eaten = 0;
		table->philosopher[i].l_fork_id = i;
		table->philosopher[i].r_fork_id = (i + 1) % n;
		table->philosopher[i].eating = FALSE;
		i++;
	}
	ph_mutex_init (table);
	return (TRUE);
}
