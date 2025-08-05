#include "../inc/philo.h"

static bool	start_sim(t_philo *philo);
static int	end_sim(t_philo *philo);
static bool	arg_has_non_digits(char *str);

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		res;

	if (ac < 5 || ac > 6)
		return (err_out(MSG_USAGE), EXIT_FAILURE);
	validate_input(ac, av);
	philo = set_the_table(ac, av);
	if (!philo)
		return(err_out("Failed to Set the Table"), EXIT_FAILURE);
	if (!start_sim(philo))
		return (err_out("Couldn't start the simulation"), EXIT_FAILURE);
	res = end_sim(philo);
	sem_cleanup(philo);
	free_philo(philo);

	if (res == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// ? each philo is now it's own process, hence fork.

static bool start_sim(t_philo *philo)
{
	int		i;
	pid_t	pid;

	philo->start_time = get_current_time() + (philo->philo_count * 20);
	i = -1;
	while (++i < philo->philo_count)
	{
		pid = fork();
		if (pid == -1)
			return (err_free("error while forking", philo), false);
		else if (pid > 0)
			philo->arr_pid[i] = pid;
		else if (pid == 0)
		{
			philo->running_proc = philo->philosophers[i];
			p_act_init_cycle(philo);
		}
	}
	if (!activate_terminators(philo))
		return (false);
	return (true);
}

static int end_sim(t_philo *philo)
{
	int	i;
	int	exit_code;

	delay_thread(philo->start_time);
	while (get_sim_stop(philo) == false)
	{
		i = 0;
		while (i < philo->philo_count)
		{
			exit_code = kill_the_child(philo, &philo->arr_pid[i]);
			if (exit_code == 0)
			{
				i++;
				continue ;
			}
			sem_wait(philo->sem_stops);
			philo->sim_stop = true;
			sem_post(philo->sem_sated);
			sem_post(philo->sem_death);
			sem_post(philo->sem_stops);
			return (exit_code);
			i++;
		}
	}
	return (0);
}

static bool arg_has_non_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (true);
		i++;
	}
	return (false);
}

// ? waits for a philo process to exit, if it does so with an error
// ? then kill all other philo processes
static int	kill_the_child(t_philo *philo, pid_t *pid)
{
	int	philo_exit_code;
	int	exit_code;

	if (*pid && waitpid(*pid, &philo_exit_code, WNOHANG) != 0
			&& WIFEXITED(philo_exit_code))
	{
		exit_code = WEXITSTATUS(philo_exit_code);
		if (exit_code == EXIT_PHILO_DEATH)
			return (kill_philo_processes(philo, 1));
		if (exit_code == EXIT_PTHREAD_ERR || exit_code == EXIT_SEM_ERR)
			return (kill_philo_processes(philo, -1));
		if (exit_code == EXIT_PHILO_SATED)
		{
			philo->sated_phils += 1;
			return (1);
		}
	}
	return (0);
}
