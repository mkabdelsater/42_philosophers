#include "../inc/philo.h"


// ? flag meaning in fcntl.h (just hover over them in VSC)

bool	init_shared_semaphores(t_philo *philo)
{
	unlink_shared_semaphores();
	philo->sem_forks = sem_open(SEM_FORKS, O_CREAT,
		S_IRUSR | S_IWUSR, philo->philo_count);
	if (philo->sem_forks == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->sem_write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_write == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->sem_sated = sem_open(SEM_SATED, O_CREAT, S_IRUSR | S_IWUSR,
		 philo->philo_count);
	if (philo->sem_sated == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->sem_death = sem_open(SEM_VITAL, O_CREAT, S_IRUSR | S_IWUSR,
		philo->philo_count);
	if (philo->sem_death == SEM_FAILED)
		return (handle_sem_error(philo), false);
	philo->sem_stops = sem_open(SEM_PAUSE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (philo->sem_stops == SEM_FAILED)
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

void	philo_proc_sleep(time_t duration)
{
	time_t	wake_up_time;

	wake_up_time = get_current_time() + duration;
	while (get_current_time() < wake_up_time)
	{
		usleep(100);
	}
}