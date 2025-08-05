#include "../inc/philo.h"

static bool	start_sim(t_philo *philo);
static void end_sim(t_philo *philo);
static bool arg_has_non_digits(char *str);

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac < 5 || ac > 6)
		return (err_out(MSG_USAGE), EXIT_FAILURE);
	validate_input(ac, av);
	philo = set_the_table(ac, av);
	if (!philo)
		return(err_out("Failed to Set the Table"), EXIT_FAILURE);
	if (!start_sim(philo))
		return (err_out("Couldn't start the simulation"), EXIT_FAILURE);
	end_sim(philo);
	return (EXIT_SUCCESS);
}

// ? each philo is now it's own process, hence fork.

static bool start_sim(t_philo *philo)
{
	int		i;
	pid_t	pid;

	philo->start_time = get_current_time() + (philo->philo_count * 20);
	i = -1;
	while (++i < philo->philo_count)
	{
		pid = fork();
		if (pid == -1)
			return (err_free("error while forking", philo), false);
		else if (pid > 0)
			philo->arr_pid[i] = pid;
		else if (pid == 0)
		{
			philo->running_proc = philo->philosophers[i];
			p_act_init_cycle(philo);
		}
	}
	if (!activate_terminators(philo))
		return (false);
	return (true);
}

static void end_sim(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->philo_count)
	{
		pthread_join(philo->philosophers[i]->thread, NULL);
		i++;
	}
	if (philo->philo_count > 1)
		pthread_join(philo->hunger_terminator, NULL);
	destroy_mutexes(philo);
	free_philo(philo);
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

