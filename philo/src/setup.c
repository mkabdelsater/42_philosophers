#include "../inc/philo.h"

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