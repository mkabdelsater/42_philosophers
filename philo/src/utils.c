#include "../inc/philo.h"

void	err_out(char *msg)
{
	printf(RED"Error:"NC" %s\n", msg);
	exit(EXIT_FAILURE);
}