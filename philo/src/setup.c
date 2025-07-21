#include "../inc/philo.h"


// ? if we let philosophers take forks normally, having an odd number of philos
// ? causes the following problem, taking 3 philos for example, in one cycle:
// ? p_0 takes f_0, p_1 takes f_1, p_2 takes f_2
// ? each philo holds one fork, and attempts to take a fork held by the other
// ? we get a deadlock right off the bat!
// ? to avoid this, we make odd even numbered philos start by attempting to take
// ? an odd fork, guarantteeing that either them or the next philo fails
// ? to take a fork, we get:
// ? p_0 wants f_0 then f_1
// ? p_1 wants f_2 then f_1
// ? p_2 wants f_2 then f_0, f_2 will have been taken, causing them to wait.

static void assign_forks(t_philosopher *philosopher)
{
	int	ph_id;
	int	philo_count;

	ph_id = philosopher->id;
	philo_count = philosopher->philo->philo_count;
	if (ph_id % 2 == 1)
	{
		philosopher->fork[0] = (ph_id + 1) % philo_count;
		philosopher->fork[1] = ph_id;
	}
	else
	{
		philosopher->fork[0] = ph_id;
		philosopher->fork[1] = (ph_id + 1) % philo_count;
	}
}

static t_philosopher	**usher_the_guests(t_philo *philo)
{
	t_philosopher	**philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philosopher) * philo->philo_count);
	if (!philosophers)
		return (err_out("failed to alloc space in usher_the_guests"), NULL);
	i = 0;
	while (i < philo->philo_count)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		if (!philosophers[i])
			return (err_out("failed to alloc space in usher_the_guests"), NULL);
		if (pthread_mutex_init(&philosophers[i]->meal_time_lock, 0) != 0)
			return (err_out("call to pthread_mutex_init returnd nonzero"), NULL);
		philosophers[i]->philo = philo;
		philosophers[i]->id = i;
		philosophers[i]->meals_had = 0;
		assign_forks(philosophers[i]);
		i++;
	}
	return (philosophers);
}

// ? @16 do I check the max number of meals? if it's 0 I print "can't be 0"

t_philo	*set_the_table(int ac, char **av, int i)
{
	t_philo	*philo;

	philo = (t_philo*)(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_count = ft_atoi(av[1]);
	philo->til_death = ft_atoi(av[2]);
	philo->til_meal = ft_atoi(av[3]);
	philo->til_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->max_meals = ft_atoi(av[5]);
	else
		philo->max_meals = -1;
	philo->sim_stop = false;
}