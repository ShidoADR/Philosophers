#ifndef STRUCT_H
# define STRUCT_H

#include <bits/pthreadtypes.h>
# include <pthread.h>

typedef int	t_bool;
typedef struct s_data t_data;

typedef struct s_philo
{
	int				meal_eaten;
	short			fork;
	short			l_fork_id;
	short			r_fork_id;
	t_bool			eating;
	t_data			*data;
	long long		last_meal;
	pthread_t		thread;
}	t_philo;

struct s_data
{
	int				n_must_eat;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	short			n_philosophers;
	t_bool			is_dead;
	t_bool			is_all_eaten;
	long long		time_to_start;
	pthread_t		monitor;
	struct s_philo	philosopher[200];
	pthread_mutex_t	fork_lock[200];
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	check_lock;
};

#endif
