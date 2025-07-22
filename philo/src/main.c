#include "../inc/philo.h"

static void	start_sim(t_philo *philo);
static void stop_sim(t_philo *philo);
static bool arg_has_non_digits(char *str);

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		err_out(MSG_USAGE);
	validate_input(ac, av);
	philo = set_the_table(ac, av);
	if (!philo)
		return(err_out("Failed to Set the Table"), EXIT_FAILURE);
	// if (!start_simulation(philo))
	// 	err_out("Couldn't start the simulation");
	// end_simulation(philo);
	return (EXIT_SUCCESS);
}

static bool start_sim(t_philo *philo)
{
	int	i;
	int	res;

	i = 0;
	philo->start_time = get_start_time() + (philo->philo_count * 200);
	while (i < philo->philo_count)
	{
		res = pthread_create(&philo->philosophers[i]->thread,
			NULL, &p_routines, philo->philosophers);
		if (res != 0)
			return (err_free("philo thread creation failed", philo), false);
		i++;
	}
	if (philo->philo_count &&
		thread_create(&philo->terminator, NULL, &terminator, philo) != 0)
			return (err_free("terminator thread create failed", philo), false);
	return (true);

}

static bool arg_has_non_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

void	validate_input(int ac, char **av)
{
	int		i;
	int		nbr;
	char	*arg;

	i = 1;
	while (i < ac)
	{
		arg = av[i];
		if (arg_has_non_digits(arg))
			err_out(ERR_NON_INT);
		nbr = ft_atoi(arg);
		if (nbr <= 0)
			err_out(ERR_NON_INT);
		if (i == 1 && (nbr <= 0 || nbr > PHILO_CAP))
			err_out("number of philosophers exceeds cap ("STR_PHILO_CAP")");
		i++;
	}
}

// static void start_simulation(t_philo *philo)
// {
// 	int	i;
// 	philo->start_time;
// }
