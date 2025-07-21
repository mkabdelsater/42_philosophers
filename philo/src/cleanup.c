#include "../inc/philo.h"

void	free_philo(t_philo *philo)
{
	int	i;

	if(!philo)
		return ;
	if (philo->fork_locks)
		free(philo->fork_locks);
	if (!philo->philosophers)
		return (free(philo));

	i = 0;
	while (i < philo->philo_count)
	{
		if (philo->philosophers[i])
			free(philo->philosophers[i]);
		i++;
	}
	free(philo->philosophers);
	free(philo);
}