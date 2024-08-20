#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

typedef int	t_bool;

typedef struct s_data
{
	int				meal_eaten;
	long			last_meal;
	long			time_to_start;
	short			id;
	t_bool			is_dead;
	pthread_mutex_t	fork;
}	t_data;

typedef struct s_philo
{
	int				n_must_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	short			n_philosophers;
	pthread_t		thread[200];
	struct s_data	data[200];
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}	t_philo;

#endif
