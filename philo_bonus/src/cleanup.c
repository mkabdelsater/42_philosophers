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
	sem_close(philo->sem_forks);
	sem_close(philo->sem_write);
	sem_close(philo->sem_sated);
	sem_close(philo->sem_death);
	sem_close(philo->sem_stops);
	unlink_shared_semaphores();
	err_free("Semaphore init failed", philo);
}

// ? exit_philo_proc exits the child process generated for each philosopher
// ? and performs the necessary cleanup

void	exit_philo_proc(t_philo *philo, int exit_code)
{
	sem_post(philo->running_proc->sem_meals);
	pthread_join(philo->running_proc->proc_terminator, NULL);
	if (exit_code == EXIT_SEM_ERR)
		err_out("Could not create semaphore");
	if (exit_code == EXIT_PTHREAD_ERR)
		err_out("Could not create thread");
	sem_close(philo->running_proc->sem_forks);
	sem_close(philo->running_proc->sem_write);
	sem_close(philo->running_proc->sem_sated);
	sem_close(philo->running_proc->sem_death);
	sem_close(philo->running_proc->sem_meals);
	free_philo(philo);
	exit(exit_code);
}