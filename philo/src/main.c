#include "../inc/philo.h"

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
// 	unsigned int	i;
// 	phi
// }

int	main(int ac, char **av)
{
	// t_philo	*philo;

	// philo = NULL;
	if (ac < 5 || ac > 6)
		err_out(MSG_USAGE);
	validate_input(ac, av);
	// philo = set_the_table(ac, av);
	// if (!philo)
	// 	err_out("Failed to Set the Table");
	// if (!start_simulation(philo))
	// 	err_out("Couldn't start the simulation");
	// end_simulation(philo);
	return (EXIT_SUCCESS);
}