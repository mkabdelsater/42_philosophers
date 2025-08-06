/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:56:28 by moabdels          #+#    #+#             */
/*   Updated: 2025/08/06 15:03:27 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ! ??? why time in ms?
time_t	get_current_time(void)
{
	struct timeval		teval;

	gettimeofday(&teval, NULL);
	return ((teval.tv_sec * 1000) + (teval.tv_usec) / 1000);
}

// ! ??? this is used for synchronization?
void	delay_thread(time_t t)
{
	while (get_current_time() < t)
		continue ;
}

void	err_free(char *msg, t_philo *philo)
{
	if (philo)
		free_philo(philo);
	printf(RED"Error:"NC" %s\n", msg);
}

void	err_out(char *msg)
{
	printf(RED"Error:"NC" %s\n", msg);
}
