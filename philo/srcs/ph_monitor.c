#include "../headers/philosophers.h"
#include <unistd.h>

t_bool	check_death(t_data *table)
{
	short	i;
	short	n;

	i = 0;
	n = table->n_philosophers;
	while (i < n)
	{
		if (is_deceased (table, &table->philosopher[i]) == TRUE)
		{
			pthread_mutex_lock (&table->death_lock);
			print_death (table->philosopher[i].fork, table);
			table->is_dead = TRUE;
			pthread_mutex_unlock (&table->death_lock);
			return (TRUE);
		}
		i++;
	}
	usleep (1);
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
		pthread_mutex_lock (&table->check_lock);
		if (table->philosopher[i].meal_eaten == table->n_must_eat)
			count_finish_eating ++;
		pthread_mutex_unlock (&table->check_lock);
		i++;
	}
	if (count_finish_eating == table->n_philosophers)
	{
		pthread_mutex_lock (&table->death_lock);
		table->is_dead = TRUE;
		pthread_mutex_unlock (&table->death_lock);
		return (TRUE);
	}
	usleep (1);
	return (FALSE);
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
	pthread_create (&(table->monitor), NULL, observe, table);
}
