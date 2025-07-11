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

bool	is_valid_input(int ac, char **av)
{
	int		i;
	int		nbr;
	char	*arg;

	i = 1;
	while (i < ac)
	{
		arg = av[i];
		if (arg_has_non_digits(arg))
			return(err_out(ERR_NON_INT), false);
		nbr = ft_atoi(arg);
		if (nbr <= 0)
			return (err_out(ERR_NON_INT), false);
		if (i == 1 && (nbr <= 0 || nbr > PHILO_CAP))
			return (err_out("That's too many philosophers...\n"), false);
		i++;
	}
	return (true);
}