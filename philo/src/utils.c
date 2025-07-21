#include "../inc/philo.h"

// ! ??? why time in ms?
time_t	get_start_time(void)
{
	struct timeval		teval;
	gettimeofday(&teval, NULL);
	return ((teval.tv_sec * 1000) + (teval.tv_usec) / 1000);
}

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