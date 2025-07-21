#include "../inc/philo.h"

void	err_free(char *msg, t_philo *philo)
{
	if (philo)
		free_philo(philo);
	printf(RED"Error:"NC" %s\n", msg);
}

void	err_out(char *msg)
{
	printf(RED"Error:"NC" %s\n", msg);
}