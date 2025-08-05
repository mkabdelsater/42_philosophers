#include "../inc/philo.h"


static bool	can_conclude(t_philo *phile, t_philosopher *p);

// * terminator is a thread that checks if either a philo died
// * or if all philos had enough meals, ending the sim in those cases

void		*proc_terminator(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->max_meals == 0)
		return (NULL);

	sem_wait(philo->running_proc->sem_death);
	sem_wait(philo->running_proc->sem_sated);
	delay_thread(philo->start_time);
	while (can_conclude(philo, philo->running_proc))
	{
		usleep(1000);
		continue;
	}
	return (NULL);
}

void		*hunger_terminator(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->philo_count == 1)
		return (NULL);
	delay_thread(philo->start_time);
	if (get_sim_stop(philo) == true)
		return (NULL);
	sem_wait(philo->sem_death);
	if (get_sim_stop(philo) == true)
		return (NULL);
	sem_wait(philo->sem_stops);
	philo->sim_stop = true;
	kill_philo_processes(philo, EXIT_SUCCESS);
	sem_post(philo->sem_sated);
	sem_post(philo->sem_stops);
	return (NULL);
}

void		*sated_terminator(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->max_meals < 0 || philo->til_death == 0
		|| philo->philo_count == 1)
		return (NULL);
	delay_thread(philo->start_time);
	while (philo->sated_phils < philo->philo_count)
	{
		if (get_sim_stop(philo) == true)
			return (NULL);
		sem_wait(philo->sem_sated);
		if (get_sim_stop(philo) == false)
			philo->sated_phils += 1;
		else
			return (NULL);
	}
	sem_wait(philo->sem_stops);
	philo->sim_stop = true;
	kill_philo_processes(philo, EXIT_SUCCESS);
	sem_post(philo->sem_death);
	sem_post(philo->sem_stops);
	return (NULL);
}

int			kill_philo_processes(t_philo *philo, int exit_code)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		kill(philo->arr_pid[i], SIGKILL);
		i++;
	}
	exit(exit_code);
}

static bool	can_conclude(t_philo *philo, t_philosopher *p)
{
	sem_wait(p->sem_meals);
	if (get_current_time() - p->since_last_meal >= philo->til_death)
	{
		print_status(p, true, DEAD);
		sem_post(philo->running_proc->sem_death);
		sem_post(p->sem_meals);
		return (true);
	}
	if (philo->max_meals != -1 && p->sated == false
		&& p->meals_had >= philo->max_meals)
	{
		sem_post(p->sem_sated);
		p->sated = true;
	}
	sem_post(p->sem_meals);
	return (false);
}