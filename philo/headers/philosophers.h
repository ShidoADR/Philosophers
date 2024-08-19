#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "color.h"
# include "struct.h"

# define TRUE 1
# define FALSE 0

int	is_numeric(char *number);
int	check_error(int ac, char *av[]);

#endif
