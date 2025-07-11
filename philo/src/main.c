#include "../inc/philo.h"

void	err_out(char *msg)
{
	printf(RED"Error:"NC" %s\n", msg);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	philo = NULL;
	if (ac != 5 || ac != 6)
		err_out(MSG_USAGE);
	if (!input_is_valid(ac, av))
		err_out("Input was Invalid");
	philo = set_the_table(ac, av, 1);
	if (!philo)
		err_out("Failed to Set the Table");
	if (!start_simulation(philo))
		err_out("Couldn't start the simulation");
	end_simulation(philo);
	return (EXIT_SUCCESS);
}