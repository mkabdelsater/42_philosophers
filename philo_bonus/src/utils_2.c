#include "../inc/philo.h"

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

bool	activate_terminators(t_philo *philo)
{
	int	res;

	res = pthread_create(&philo->hunger_terminator,
			NULL, &hunger_terminator, philo);
	if (res != 0)
		return (err_free("failed to create hunger terminator", philo), false);
	res = pthread_create(&philo->sated_terminator,
			NULL, &sated_terminator, philo);
	if (res != 0)
		return (err_free("failed to create sated terminator", philo), false);
	return (true);
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
		{
			err_out(ERR_NON_INT);
			exit(EXIT_FAILURE);
		}
		nbr = ft_atoi(arg);
		if (nbr <= 0)
		{
			err_out(ERR_NON_INT);
			exit(EXIT_FAILURE);
		}
		if (i == 1 && (nbr <= 0 || nbr > PHILO_CAP))
		{
			err_out("number of philosophers exceeds cap ("STR_PHILO_CAP")");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

bool arg_has_non_digits(char *str)
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