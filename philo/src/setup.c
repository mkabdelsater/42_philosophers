#include "../inc/philo.h"

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