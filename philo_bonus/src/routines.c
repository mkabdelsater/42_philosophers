#include "../inc/philo.h"

static void	p_act_think(t_philosopher *p, bool quiet);
static void	p_act_eat_sleep(t_philosopher *p);
static void	p_act_cycle(t_philosopher *p);
static void	p_act_alone(t_philosopher *p);

/**
 * * philos with even numbers start by thinking, delaying their
 * * meal time by a small margin, this lets odds grab their forks
 * * first
 * ! but didn't we already solve this?
 * TODO: try removing the odd number thing
 */

void	p_act_init_cycle(t_philo *philo)
{
	t_philosopher	*p;

	p = philo->running_proc;
	if (p->philo->philo_count == 1)
		p_act_alone(p);
	init_intercom(philo, p);
	if (p->philo->max_meals == 0)
	{
		sem_post(p->sem_sated);
		exit_philo_proc(philo, EXIT_PHILO_SATED);
	}
	if (p->philo->til_death == 0)
	{
		sem_post(p->sem_death);
		exit_philo_proc(philo, EXIT_PHILO_DEATH);
	}
	sem_wait(p->sem_meals);
	p->since_last_meal = p->philo->start_time;
	sem_post(p->sem_meals);
	delay_thread(p->philo->start_time);
	p_act_cycle(p);
}

static void p_act_cycle(t_philosopher *p)
{
	if (p->id % 2)
		p_act_think(p, true);
	while (true)
	{
		p_act_eat_sleep(p);
		p_act_think(p, false);
	}
}

// TODO: the 1 @63 should probably be explicitly globalized as DELAY
static void p_act_think(t_philosopher *p, bool quiet)
{
	time_t	til_think;

	sem_wait(p->sem_meals);
	til_think = (p->philo->til_death
			- (get_current_time() - p->since_last_meal)
			- p->philo->til_meal) / 2;
	sem_wait(p->sem_meals);
	if (til_think <= 0)
		til_think = 1;
	// if (til_think == 0 && quiet == true)
	// 	til_think = 1;
	if (til_think > PHILO_CAP * 3)
		til_think = PHILO_CAP;
	if (!quiet)
		print_status(p, false, THINKING);
	philo_proc_sleep(til_think);
}

static void p_act_eat_sleep(t_philosopher *p)
{
	p_act_grab_fork(p);
	p_act_grab_fork(p);
	print_status(p, false, EATING);
	sem_wait(p->sem_meals);
	p->since_last_meal = get_current_time();
	sem_post(p->sem_meals);
	philo_proc_sleep(p->philo->til_meal);
	print_status(p, false, SLEEPING);
	sem_post(p->sem_forks);
	sem_post(p->sem_forks);
	sem_wait(p->sem_meals);
	p->forks_held -= 2;
	p->meals_had += 1;
	sem_post(p->sem_meals);
	philo_proc_sleep(p->philo->til_sleep);
}

// this was returning NULL for some reason but the value wasn't
// being used meaningfully
static void p_act_alone(t_philosopher *p)
{
	p->sated = sem_open(SEM_SATED, O_CREAT, S_IRUSR | S_IWUSR,
		p->philo->philo_count);
	if (p->sem_sated == SEM_FAILED)
	{
		free_philo(p->philo);
		exit(EXIT_SEM_ERR);
	}
	delay_thread(p->philo->start_time);
	if (p->philo->max_meals == 0)
	{
		sem_post(p->sated);
		exit(EXIT_PHILO_SATED);
	}
	print_status(p, false, HAS_FORK_1);
	philo_proc_sleep(p->philo->til_death);
	print_status(p, false, DEAD);
	free_philo(p->philo);
	exit(EXIT_PHILO_DEATH);
}