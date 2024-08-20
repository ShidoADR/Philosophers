#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "color.h"
# include "struct.h"

# define TRUE 1
# define FALSE 0

t_bool	is_numeric(char *number);
t_bool	check_error(int ac, char *av[]);
long	ft_atol(const char *nptr);

#endif
