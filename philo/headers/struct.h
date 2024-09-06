#ifndef STRUCT_H
# define STRUCT_H

# include <pthread.h>

# define THREAD_MAX 124501

typedef int				t_bool;
typedef int				t_error_flag;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				fork;
	int				meal_eaten;
	int				l_fork_id;
	int				r_fork_id;
	t_bool			eating;
	t_data			*data;
	long long		last_meal;
	pthread_t		thread;
	pthread_mutex_t	fork_lock;
}	t_philo;

struct s_data
{
	int				n_must_eat;
	int				n_philosophers;
	long			time_to_die;
	long			time_to_sleep;
	long			time_to_eat;
	t_bool			is_dead;
	t_bool			is_all_eaten;
	long long		time_to_start;
	pthread_t		monitor;
	struct s_philo	*philosopher;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	check_lock;
};

#endif
