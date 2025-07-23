#include "../inc/philo.h"

static void p_act_alone(t_philosopher *p);
static void p_act_think(t_philosopher *p, bool quiet);
static void p_act_eat_sleep(t_philosopher *p);


/**
 * * philos with even numbers start by thinking, delaying their
 * * meal time by a small margin, this lets odds grap their forks
 * * first
 * ! but didn't we already solve this?
 * TODO: try removing the odd number thing
 */
void	*p_act_init_cycle(void *phl)
{
	t_philosopher	*p;

	p = (t_philosopher*)phl;
	if (p->philo->max_meals == 0)
		return (NULL);
	pthread_mutex_lock(&p->meal_time_lock);
	p->since_last_meal = p->philo->start_time;
	pthread_mutex_unlock(&p->meal_time_lock);
	delay_thread(p->philo->start_time);
	//when does this happen? if at time of death why exactly 0?
	// why are we doing this?
	if (p->philo->til_death == 0)
		return (NULL);
	if (p->philo->philo_count == 1)
		return (p_act_alone(p), NULL);
	else if (p->id % 2 != 0)
		p_act_think(p, true);
	while (!get_sim_stop(p->philo))
	{
		p_act_eat_sleep(p);
		p_act_think(p, false);
	}
	return (NULL);
}

void	philo_thread_sleep(t_philo *philo, time_t duration)
{
	time_t	wake_up_time;

	wake_up_time = get_current_time() + duration;
	while (get_current_time() < wake_up_time)
	{
		if (get_sim_stop(philo))
			break ;
		usleep(100);
	}
}

static void p_act_think(t_philosopher *p, bool quiet)
{
	time_t	til_think;

	pthread_mutex_lock(&p->meal_time_lock);
	til_think = (p->philo->til_death - (get_current_time() - p->since_last_meal)
				- p->philo->til_meal) / 2;
	pthread_mutex_unlock(&p->meal_time_lock);
	if (til_think < 0)
		til_think < 0;
	if (til_think == 0 && quiet == true)
		til_think = 1;
	// WHAT ARE YOU ON ABOUT!!!???
	if (til_think > 600)
		til_think = 200;
	if (!quiet)
		print_status(p, false, THINKING);
	philo_thread_sleep(p->philo, til_think);
}

static void p_act_eat_sleep(t_philosopher *p)
{
	pthread_mutex_lock(&p->philo->fork_locks[p->fork[0]]);
	print_status(p, false, HAS_FORK_1);
	pthread_mutex_lock(&p->philo->fork_locks[p->fork[1]]);
	print_status(p, false, HAS_FORK_2);
	print_status(p, false, EATING);
	pthread_mutex_lock(&p->meal_time_lock);
	p->since_last_meal = get_current_time();
	pthread_mutex_unlock(&p->meal_time_lock);
	philo_thread_sleep(p->philo, p->philo->til_meal);
	if (get_sim_stop(p->philo) == false)
	{
		pthread_mutex_lock(&p->meal_time_lock);
		p->meals_had += 1;
		pthread_mutex_unlock(&p->meal_time_lock);
	}
	print_status(p, false, SLEEPING);
	pthread_mutex_unlock(&p->philo->fork_locks[p->fork[1]]);
	pthread_mutex_unlock(&p->philo->fork_locks[p->fork[0]]);
	philo_thread_sleep(p->philo, p->philo->til_sleep);
}

// this was returning NULL for some reason but the value wasn't
// being used meaningfully
static void p_act_alone(t_philosopher *p)
{
	pthread_mutex_lock(&p->philo->fork_locks[p->fork[0]]);
	print_status(p, false, HAS_FORK_1);
	philo_thread_sleep(p->philo, p->philo->til_death);
	print_status(p, false, DEAD);
	pthread_mutex_unlock(&p->philo->fork_locks[p->fork[0]]);
}