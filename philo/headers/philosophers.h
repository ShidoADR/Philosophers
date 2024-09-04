#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "color.h"
# include "struct.h"

# define FREE 3
# define IN_USE 2
# define TRUE 1
# define FALSE 0
# define PHILO_NUMBER -1
# define ARG_VALUE -2
# define INPUT_VALUE -3
# define ARG_NUMBER -4

/*
** file == srcs/ph_error_handler.c
*/
t_bool			is_numeric(char *number);
t_bool			check_error(char *av[]);
t_error_flag	is_valid_arguments(int ac, char *av[], t_data *table);

/*
** file == srcs/ph_init_data.c
*/
void			ph_init_data(int ac, char *av[], t_data *table);
t_bool			ph_init_philo(int ac, char *av[], t_data *table);

/*
** file == srcs/ph_lib.c
*/
long			ft_atol(const char *nptr);
long long		ph_get_current_time(void);
void			ph_usleep(long long time, t_data *table);

/*
** file == srcs/ph_monitor.c
*/
t_bool			check_death(t_data *table);
t_bool			check_eaten(t_data *table);
void			*observe(void *data);
void			monitoring(t_data *table);

/*
** file == srcs/ph_mutex_utils.c
*/
void			ph_mutex_init(t_data *table);
void			ph_mutex_destroy(t_data *table);

/*
** file == srcs/ph_print.c
*/
void			print_action(short id, char *message, t_data *table);
void			print_death(short id, t_data *table);
void			print_error(t_error_flag flag);

/*
** file == srcs/ph_routine.c
*/
void			*philosophize(void *data);
void			start_routine(t_data *t);
void			ph_routine(t_data *table);

/*
** file == srcs/ph_thread_utils.c
*/
t_bool			dead_body_detected(t_data *table);
t_bool			is_deceased(t_data *table, t_philo *ph);
void			ph_join_thread(t_data *table);

/*
** file == srcs/rt_eat.c
*/
void			ph_take_fork(t_philo *ph);
void			ph_drop_fork(t_philo *ph);
void			rt_eat(t_data *table, t_philo *ph);

/*
** file == srcs/rt_sleep_think.c
*/
void			rt_think(t_data *table, t_philo *ph);
void			rt_sleep(t_data *table, t_philo *ph);

#endif
