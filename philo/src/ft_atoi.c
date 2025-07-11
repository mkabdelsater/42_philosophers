/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 11:59:01 by moabdels          #+#    #+#             */
/*   Updated: 2024/06/21 14:35:09 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TESTING INCLUDES
// #include <stdio.h>
// #include <stdlib.h>
//START
#include "libft.h"

static int	ft_iswhitespace(int c)
{
	return ((c > 8 && c < 14) || (c == 32));
}

int	ft_atoi(const char *nptr)
{
	long long int	res;
	long long int	check_overflow;
	int				sign;

	res = 0;
	sign = 1;
	while (*nptr && ft_iswhitespace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
	{
		check_overflow = res;
		res = res * 10 + sign * (*nptr - 48);
		if (res > check_overflow && sign < 0)
			return (0);
		if (res < check_overflow && sign > 0)
			return (-1);
		nptr++;
	}
	return (res);
}
//END

//TESTING

// int	main(int argc, char *argv[])
// {
// 	int		i_index;
// 	int		ft__res;
// 	int		std_res;
// 	char	*current_arg;

// 	i_index = 1;
// 	if (argc < 2)
// 	{
// 		printf("not enough args");
// 		return (1);
// 	}
// 	while (i_index < argc)
// 	{
// 		current_arg = argv[i_index];
// 		ft__res = ft_atoi(current_arg);
// 		std_res = atoi(current_arg);
// 		printf("ft__res = %d\nstd_res = %d\n", ft__res, std_res);
// 		i_index++;
// 	}

// 	return (0);
// }
