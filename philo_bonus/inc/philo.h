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

# define PHILO_CAP 250
# define STR_PHILO_CAP "250"

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

# define MSG_USAGE "usage: ./philo <numer of philosophers> <time to die> \
<time to eat> <time to sleep> <optional: number of meals to stop after>\n"
# define ERR_NON_INT "only positive integers are valid arguments, try again."

# define SEM_FORKS "/moabdels_philo_forks"
# define SEM_WRITE "/moabdels_philo_write"
# define SEM_SATED "/moabdels_philo_sated"
# define SEM_VITAL "/moabdels_philo_vital"
# define SEM_PAUSE "/moabdels_philo_pause"
# define SEM_MEALS "/moabdels_philo_meals"

# define EXIT_PTHREAD_ERR 40
# define EXIT_SEM_ERR 41
# define EXIT_PHILO_SATED 42
# define EXIT_PHILO_DEATH 43

typedef struct s_philosopher	t_philosopher;

typedef struct s_philo
{
	t_philosopher	*running_proc;
	t_philosopher	**philosophers;
	pthread_t		sated_terminator;
	pthread_t		hunger_terminator;
	time_t			til_meal;
	time_t			til_sleep;
	time_t			til_death;
	time_t			start_time;
	sem_t			*sem_stops;
	sem_t			*sem_forks;
	sem_t			*sem_write;
	sem_t			*sem_death;
	sem_t			*sem_sated;
	pid_t			*arr_pid;
	int				max_meals;
	int				sated_phils;
	int				philo_count;
	bool			sim_stop;
}	t_philo;

typedef struct s_philosopher
{
	pthread_t	proc_terminator;
	pthread_t	thread;
	t_philo		*philo;
	time_t		since_last_meal;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_death;
	sem_t		*sem_sated;
	sem_t		*sem_meals;
	int			id;
	int			meals_had;
	int			forks_held;
	char		*meals_sem_name;
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
char	*ft_strcat(char *dest, const char *src);
void	err_out(char *msg);
void	err_free(char *msg, t_philo *philo);
void	validate_input(int ac, char **av);
void	print_err_exit(char *msg);

// * reporting *
bool	get_sim_stop(t_philo *philo);
void	print_status(t_philosopher *p, bool is_terminator, t_status status);

// * time *
time_t	get_current_time(void);
void	delay_thread(time_t t);

// * cleanup *
void	free_philo(t_philo *philo);
void	exit_philo_proc(t_philo *philo, int exit_code);

// * actions *
void	*p_act_init_cycle(void *p);
void	*hunger_terminator(void *data);
void	p_act_grab_fork(t_philosopher *p);
void	philo_proc_sleep(time_t duration);
t_philo	*set_the_table(int ac, char **av);

// * semaphores *
bool	init_shared_semaphores(t_philo *philo);
void	unlink_shared_semaphores(void);
void	handle_sem_error(t_philo *philo);
void	init_intercom(t_philo *philo, t_philosopher *p);

// * terminators *
void		*proc_terminator(void *data);
void		*hunger_terminator(void *data);
void		*sated_terminator(void *data);
int			kill_philo_processes(t_philo *philo, int exit_code);

#endif