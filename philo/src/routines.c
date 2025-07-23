#include "../inc/philo.h"


/**
 * * philos with even numbers start by thinking, delaying their
 * * meal time by a small margin, this lets odds grap their forks
 * * first
 * ! but didn't we already solve this?
 * TODO: try removing the odd number thing
 */
void	*philo_actions(t_philosopher *p)
{
	if (p->philo->max_meals == 0)
		return (NULL);
	// TODO: encapsulate the blow into sync_update_* functions ?
	pthread_mutex_lock(&p->meal_time_lock);
	p->since_last_meal = p->philo->start_time;
	pthread_mutex_unlock(&p->meal_time_lock);
	delay_thread(p->philo->start_time);
	//when does this happen? if at time of death why exactly 0?
	if (p->philo->til_death == 0)
		return (NULL);
	if (p->philo->philo_count == 1)
		return (p_act_alone(p));
	else if (p->id % 2 != 0)
		p_act_think(p, true);
	while (!get_sim_stop(p->philo))
	{
		p_act_eat_sleep(p);
		p_act_think(p, false);
	}
	return (NULL);
}