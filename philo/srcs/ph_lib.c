#include "../headers/philosophers.h"
#include <pthread.h>

long	ft_atol(const char *nptr)
{
	int		i;
	long	result;
	int		sign;

	if (!nptr)
		return (0);
	i = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += (nptr[i] - 48);
		i++;
	}
	return (sign * result);
}

long long	ph_get_current_time(void)
{
	struct timeval	tv;

	gettimeofday (&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ph_usleep(long long time, t_data *table)
{
	long long	start_time;

	start_time = ph_get_current_time ();
	while ((ph_get_current_time() - start_time) < time)
	{
		if (dead_body_detected (table) == TRUE)
			break ;
		usleep (500);
	}
}
