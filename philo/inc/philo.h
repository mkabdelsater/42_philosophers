/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabdels <moabdels@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:53:19 by moabdels          #+#    #+#             */
/*   Updated: 2025/08/06 14:56:58 by moabdels         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int				philo_count;
	time_t			start_time;
	time_t			til_death;
	time_t			til_meal;
	time_t			til_sleep;
	int				max_meals;
	bool			sim_stop;
	pthread_mutex_t	sim_stop_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*fork_locks;
	t_philosopher	**philosophers;
	pthread_t		terminator;
}	t_philo;

typedef struct s_philosopher
{
	pthread_t			thread;
	int					id;
	int					meals_had;
	int					fork[2];
	pthread_mutex_t		meal_time_lock;
	time_t				since_last_meal;
	t_philo				*philo;
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
void	*terminator(void *data);
t_philo	*set_the_table(int ac, char **av);

#endif