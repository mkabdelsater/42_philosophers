#include "../inc/philo.h"

static bool	open_shared_semaphores(t_philosopher *p);
static bool	open_process_semaphores(t_philosopher *p);

void		init_intercom(t_philo *philo, t_philosopher *p)
{
	if (philo->philo_count == 1)
		return ;
	sem_unlink(p->meals_sem_name);
	if (!open_shared_semaphores(p))
		exit_philo_proc(philo, EXIT_SEM_ERR);
	if (!open_process_semaphores(p))
		exit_philo_proc(philo, EXIT_SEM_ERR);
	if (pthread_create(&p->proc_terminator, NULL, &proc_terminator, philo) != 0)
		exit_philo_proc(philo, EXIT_PTHREAD_ERR);
	return ;
}

// ? these are shared between the parent and all child processes
static bool	open_shared_semaphores(t_philosopher *p)
{
	p->sem_forks = sem_open(SEM_FORKS, O_CREAT, S_IRUSR | S_IWUSR,
			p->philo->philo_count);
	if (p->sem_forks == SEM_FAILED)
		return (false);
	p->sem_write = sem_open(SEM_WRITE, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (p->sem_write == SEM_FAILED)
		return (false);
	p->sem_sated = sem_open(SEM_SATED, O_CREAT, S_IRUSR | S_IWUSR,
			p->philo->philo_count);
	if (p->sem_sated == SEM_FAILED)
		return (false);
	p->sem_death = sem_open(SEM_VITAL, O_CREAT, S_IRUSR | S_IWUSR,
			p->philo->philo_count);
	if (p->sem_death == SEM_FAILED)
		return (false);
	return (true);
}

// ? shared between each process and it's terminator
// TODO: 🐸 ~ thread safety is my passion ~ 🐸
static bool open_process_semaphores(t_philosopher *p)
{
	p->sem_meals = sem_open(p->meals_sem_name, O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (p->sem_meals == SEM_FAILED)
		return (false);
	sem_unlink(p->meals_sem_name);
	return (true);
}