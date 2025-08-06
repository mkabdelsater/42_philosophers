/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:27:39 by moabdels          #+#    #+#             */
/*   Updated: 2025/08/06 14:50:08 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// ? if you don't do *name = '\0' you get an invalid free because of strcat (?)

char	*get_sem_name(char *str, int id)
{
	char	*name;
	char	*temp;
	int		i;
	int		digits;

	digits = 1;
	i = id;
	while (i)
	{
		digits++;
		i /= 10;
	}
	i = ft_strlen(str) + digits;
	name = malloc (sizeof(char) * (i + 1));
	if (name == NULL)
		return (err_out("Alloc failure for sem_name"), NULL);
	*name = '\0';
	name = ft_strcat(name, str);
	temp = ft_itoa(id, digits);
	name = ft_strcat(name, temp);
	free(temp);
	return (name);
}

// TODO: explanation for meal_sem_name goes here
// ?
// ?

static t_philosopher	**usher_the_guests(t_philo *philo)
{
	t_philosopher	**ps;
	int				i;

	ps = malloc(sizeof(t_philosopher) * (philo->philo_count + 1));
	if (!ps)
		return (err_free("failed to alloc in usher_the_guests", philo), NULL);
	i = 0;
	while (i < philo->philo_count)
	{
		ps[i] = malloc(sizeof(t_philosopher));
		if (!ps[i])
			return (err_free("failed alloc in usher_the_guests", philo), NULL);
		ps[i]->philo = philo;
		ps[i]->id = i;
		ps[i]->meals_sem_name = get_sem_name(SEM_MEALS, ps[i]->id + 1);
		if (ps[i]->meals_sem_name == NULL)
			return (err_free("failed to create meals_sem_name", philo), NULL);
		ps[i]->meals_had = 0;
		ps[i]->forks_held = 0;
		ps[i]->sated = false;
		i++;
	}
	return (ps);
}

t_philo	*set_the_table(int ac, char **av)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_count = ft_atoi(av[1]);
	philo->til_death = ft_atoi(av[2]);
	philo->til_meal = ft_atoi(av[3]);
	philo->til_sleep = ft_atoi(av[4]);
	philo->sated_phils = 0;
	philo->sim_stop = false;
	if (ac == 6)
		philo->max_meals = ft_atoi(av[5]);
	else
		philo->max_meals = -1;
	if (!init_shared_semaphores(philo))
		return (NULL);
	philo->philosophers = usher_the_guests(philo);
	if (!philo->philosophers)
		return (NULL);
	philo->arr_pid = malloc(sizeof(pid_t) * philo->philo_count);
	if (!philo->arr_pid)
		return (err_free("failed to allocate arr_pid", philo), NULL);
	return (philo);
}
