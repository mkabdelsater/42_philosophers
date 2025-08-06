#include "../inc/philo.h"

bool	get_sim_stop(t_philo *philo)
{
	bool	res;

	sem_wait(philo->sem_stops);
	res = philo->sim_stop;
	sem_post(philo->sem_stops);
	return (res);
}

// * reports on philo activity, lock is there to prevent multiple threads
// * from reporting at the same time
void	print_status(t_philosopher *p, bool is_terminator, t_status status)
{
	char	*status_str;

	printf("waiting for the write semaphore\n");
	sem_wait(p->sem_write);
	if (status == DEAD)
		status_str = RED"died 💀"NC;
	else if (status == EATING)
		status_str = "is eating 🍴";
	else if (status == SLEEPING)
		status_str = "is sleeping 💤";
	else if (status == THINKING)
		status_str = "is thinking 🤔";
	else if (status == HAS_FORK_1)
		status_str = "aquired fork 1️⃣";
	else if (status == HAS_FORK_2)
		status_str = "aquired fork 2️⃣";
	printf("%ld %d %s\n",
		get_current_time() - p->philo->start_time, p->id + 1, status_str);
	if (!is_terminator)
		sem_post(p->sem_write);
	printf("write was successful\n");
}