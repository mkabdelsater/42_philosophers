/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:55:10 by moabdels          #+#    #+#             */
/*   Updated: 2025/08/06 14:57:29 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	free_philo(t_philo *philo)
{
	int	i;

	if (!philo)
		return ;
	if (philo->fork_locks)
		free(philo->fork_locks);
	if (!philo->philosophers)
		return (free(philo));
	i = 0;
	while (i < philo->philo_count)
	{
		if (philo->philosophers[i])
			free(philo->philosophers[i]);
		i++;
	}
	free(philo->philosophers);
	free(philo);
}

void	destroy_mutexes(t_philo *philo)
{
	int	i;

	while (i < philo->philo_count)
	{
		pthread_mutex_destroy(&philo->fork_locks[i]);
		pthread_mutex_destroy(&philo->philosophers[i]->meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&philo->write_lock);
	pthread_mutex_destroy(&philo->sim_stop_lock);
}
