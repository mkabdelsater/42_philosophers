#include "../inc/philo.h"


// ? flag meaning in fcntl.h (just hover over them in VSC)

bool	init_shared_semaphores(t_philo *philo)
{
	unlink_shared_semaphores();
	philo->forks = sem_open(SEM_FORKS, O_CREAT,
		S_IRUSR | S_IWUSR, philo->philo_count);
	if (philo->forks == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->write == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->sated = sem_open(SEM_SATED, O_CREAT, S_IRUSR | S_IWUSR,
		 philo->philo_count);
	if (philo->sated == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->vital = sem_open(SEM_VITAL, O_CREAT, S_IRUSR | S_IWUSR,
		philo->philo_count);
	if (philo->vital == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->pause = sem_open(SEM_PAUSE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->pause == SEM_FAILED)
		return (handle_sem_error(philo), false);
	return (true);
}

void	unlink_shared_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_WRITE);
	sem_unlink(SEM_SATED);
	sem_unlink(SEM_VITAL);
	sem_unlink(SEM_PAUSE);
}