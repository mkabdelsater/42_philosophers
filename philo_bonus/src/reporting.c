#include "../inc/philo.h"

bool	get_sim_stop(t_philo *philo)
{
	bool	res;

	res = false;
	pthread_mutex_lock(&philo->sim_stop_lock);
	if (philo->sim_stop)
		res = true;
	pthread_mutex_unlock(&philo->sim_stop_lock);
	return (res);
}

// * reports on philo activity, lock is there to prevent multiple threads
// * from reporting at the same time
void	print_status(t_philosopher *p, bool is_terminator, t_status status)
{
	char	*status_str;

	pthread_mutex_lock(&p->philo->write_lock);
	if (get_sim_stop(p->philo) && !is_terminator)
	{
		pthread_mutex_unlock(&p->philo->write_lock);
		return ;
	}
	if (status == DEAD)
		status_str = RED"FKNG DIED 💀"NC;
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
	pthread_mutex_unlock(&p->philo->write_lock);
}