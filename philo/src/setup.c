#include "../inc/philo.h"

// ? pthread_mutex_init should always return 0
static pthread_mutex_t	*alloc_fork_mutexes(t_philo *philo)
{
	pthread_mutex_t	*fork_locks;
	int				i;

	fork_locks = malloc(sizeof(pthread_mutex_t) * philo->philo_count);
	i = 0;
	if (!fork_locks)
		return (err_free("failed to alloc in alloc_fork_...", philo), NULL);
	while (i < philo->philo_count)
		pthread_mutex_init(&fork_locks[i++], 0);
	return (fork_locks);
}

static bool init_mutex_locks(t_philo *philo)
{
	philo->fork_locks = alloc_fork_mutexes(philo);
	if (!philo->fork_locks)
		return (false);
	if (pthread_mutex_init(&philo->sim_stop_lock, 0) != 0 ||
			pthread_mutex_init(&philo->write_lock, 0) != 0)
		return (err_free("Failed to init mutexes", philo), false);
}

// ? if we let philosophers take forks normally, having an odd number of philos
// ? causes the following problem, taking 3 philos for example, in one cycle:
// ? p_0 takes f_0, p_1 takes f_1, p_2 takes f_2
// ? each philo holds one fork, and attempts to take a fork held by the other
// ? we get a deadlock right off the bat!
// ? to avoid this, we make odd even numbered philos start by attempting to take
// ? an odd fork, guarantteeing that either them or the next philo fails
// ? to take a fork, we get:
// ? p_0 wants f_0 then f_1
// ? p_1 wants f_2 then f_1
// ? p_2 wants f_2 then f_0, f_2 will have been taken, causing them to wait.

static void assign_the_forks(t_philosopher *philosopher)
{
	int	ph_id;
	int	philo_count;

	ph_id = philosopher->id;
	philo_count = philosopher->philo->philo_count;
	if (ph_id % 2 == 1)
	{
		philosopher->fork[0] = (ph_id + 1) % philo_count;
		philosopher->fork[1] = ph_id;
	}
	else
	{
		philosopher->fork[0] = ph_id;
		philosopher->fork[1] = (ph_id + 1) % philo_count;
	}
}

static t_philosopher	**usher_the_guests(t_philo *philo)
{
	t_philosopher	**philosophers;
	int				i;

	philosophers = malloc(sizeof(t_philosopher) * philo->philo_count);
	if (!philosophers)
		return (err_free("failed to alloc in usher_the_guests", philo), NULL);
	i = 0;
	while (i < philo->philo_count)
	{
		philosophers[i] = malloc(sizeof(t_philosopher));
		if (!philosophers[i])
			return (err_free("failed to alloc in usher_the_guests", philo), NULL);
		if (pthread_mutex_init(&philosophers[i]->meal_time_lock, 0) != 0)
			return (err_free("call to pthread_mutex_init returnd nonzero",
						philo), NULL);
		philosophers[i]->philo = philo;
		philosophers[i]->id = i;
		philosophers[i]->meals_had = 0;
		assign_the_forks(philosophers[i]);
		i++;
	}
	return (philosophers);
}

// ? @16 do I check the max number of meals? if it's 0 I print "can't be 0"

t_philo	*set_the_table(int ac, char **av, int i)
{
	t_philo	*philo;

	philo = (t_philo*)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->philo_count = ft_atoi(av[1]);
	philo->til_death = ft_atoi(av[2]);
	philo->til_meal = ft_atoi(av[3]);
	philo->til_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->max_meals = ft_atoi(av[5]);
	else
		philo->max_meals = -1;
	philo->philosophers = usher_the_guests(philo);
	if (!philo->philosophers)
		return (NULL);

	philo->sim_stop = false;
}