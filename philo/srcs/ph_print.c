#include "../headers/philosophers.h"

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
