#include "../headers/philosophers.h"

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
