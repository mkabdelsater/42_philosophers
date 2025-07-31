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

void	destroy_mutexes(t_philo *philo)
{
	int	i;
	while (i < philo->philo_count)
	{
		pthread_mutex_destroy(&philo->fork_locks[i]);
		pthread_mutex_destroy(&philo->philosophers[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&philo->write_lock);
	pthread_mutex_destroy(&philo->sim_stop_lock);
}

void	handle_sem_error(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->write);
	sem_close(philo->sated);
	sem_close(philo->vital);
	sem_close(philo->pause);
	unlink_shared_semaphores();
	err_free("Semaphore init failed", philo);
}