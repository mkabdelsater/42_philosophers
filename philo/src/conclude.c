#include "../inc/philo.h"

static void set_sim_stop(t_philo *philo, bool val)
{
	pthread_mutex_lock(&philo->sim_stop_lock);
	philo->sim_stop = val;
	pthread_mutex_unlock(&philo->sim_stop_lock);
}

// TODO:[sanity] invert logic if this causes problems somehow
static bool ready_to_die(t_philosopher *philosopher)
{
	time_t	time;

	time = get_current_time();
	if ((time - philosopher->since_last_meal) < philosopher->philo->til_death)
		return (false);
	set_sim_stop(philosopher->philo, true);
	print_status(philosopher, true, DEAD);
	pthread_mutex_unlock(&philosopher->meal_time_lock);
	return (true);
}

// ??? why are we aquiring meal_time_lock? bad naming?
static bool	can_conclude(t_philo *philo)
{
	int		i;
	bool	sated;

	sated = true;
	i = 0;
	while (i < philo->philo_count)
	{
		pthread_mutex_lock(&philo->philosophers[i]->meal_time_lock);
		if (ready_to_die(philo->philosophers[i]))
			return (true);
		if (philo->max_meals != -1 &&
			philo->philosophers[i]->meals_had < philo->max_meals)
				sated = false;
		pthread_mutex_unlock(&philo->philosophers[i]->meal_time_lock);
		i++;
	}
	if (philo->max_meals != -1 && sated)
		return (set_sim_stop(philo, true), true);
	return (false);
}

// * terminator is a thread that checks if either a philo died
// * or if all philos had enough meals, ending the sim in those cases
// ! ??? why is this a void pointer

void	*terminator(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;

	if (philo->max_meals == 0)
		return (NULL);
	set_sim_stop(philo, false);
	delay_thread(philo->start_time);
	while (true)
	{
		if (can_conclude(philo))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}