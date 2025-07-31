#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

# define PHILO_CAP 200
# define STR_PHILO_CAP "200"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define MSG_USAGE "usage: ./philo <numer of philosophers> <time to die> \
<time to eat> <time to sleep> <optional: number of meals to stop after>\n"
# define ERR_NON_INT "only positive integers are valid arguments, try again."

typedef struct s_philosopher	t_philosopher;

typedef struct s_philo
{
	t_philosopher	*this_guy;
	t_philosopher	**philosophers;
	pthread_t		terminator_full;
	pthread_t		terminator_hunger;
	time_t			til_meal;
	time_t			til_sleep;
	time_t			til_death;
	time_t			start_time;
	sem_t			*stop;
	sem_t			*forks;
	sem_t			*write;
	sem_t			*vitals;
	sem_t			*satiety;
	pid_t			*arr_pid;
	int				max_meals;
	int				sated_phils;
	int				philo_count;
	bool			sim_stop;
}	t_philo;

typedef struct s_philosopher
{
	pthread_t	terminator;
	pthread_t	thread;
	t_philo		*philo;
	time_t		since_last_meal;
	sem_t		*forks;
	sem_t		*write;
	sem_t		*vitals;
	sem_t		*satiety;
	sem_t		*meal_time;
	int			id;
	int			meals_had;
	int			forks_held;
	char		*meal_name;
	bool		sated;
}	t_philosopher;

typedef enum e_status
{
	DEAD,
	EATING,
	SLEEPING,
	THINKING,
	HAS_FORK_1,
	HAS_FORK_2
}	t_status;

// * utils *
int		ft_atoi(const char *nptr);
void	err_out(char *msg);
void	err_free(char *msg, t_philo *philo);
void	validate_input(int ac, char **av);


// * reporting *
bool	get_sim_stop(t_philo *philo);
void	print_status(t_philosopher *p, bool is_terminator, t_status status);

// * time *
time_t	get_current_time(void);
void	delay_thread(time_t t);

// * cleanup *
void	free_philo(t_philo *philo);
void	destroy_mutexes(t_philo *philo);

// * actions *
void	*p_act_init_cycle(void *p);
void	*terminator_hunger(void *data);
t_philo	*set_the_table(int ac, char **av);

#endif