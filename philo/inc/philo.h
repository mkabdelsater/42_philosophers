#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define PHILO_CAP 200
# define STR_PHILO_CAP "200"

# ifndef DEBUG_FORMATTING
#  define DEBUG_FORMATTING 0
# endif

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

typedef struct s_philosopher	t_philosopher;

typedef struct s_philo
{
	unsigned int	philo_count;
	time_t			start_time;
	time_t			til_death;
	time_t			til_meal;
	time_t			til_sleep;
	int				must_eat_count;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philosopher	**philosophers;
	pthread_t		reaper;
}	t_philo;

typedef struct s_philosopher
{
	pthread_t			thread;
	unsigned int		id;
	unsigned int		meals_had;
	unsigned int		fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				since_last_meal;
	t_philo				*table;
}	t_philosopher;

#endif