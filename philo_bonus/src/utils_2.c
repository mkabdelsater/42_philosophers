#include "../inc/philo.h"

void	philo_proc_sleep(time_t duration)
{
	time_t	wake_up_time;

	wake_up_time = get_current_time() + duration;
	while (get_current_time() < wake_up_time)
	{
		usleep(100);
	}
}

void	p_act_grab_fork(t_philosopher *p)
{
	sem_wait(p->sem_forks);
	sem_wait(p->sem_meals);
	if (p->forks_held <= 0)
		print_status(p, false, HAS_FORK_1);
	if (p->forks_held == 1)
		print_status(p, false, HAS_FORK_2);
	sem_post(p->sem_meals);
}