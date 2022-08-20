/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 13:21:57 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:49:06 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_sems_open(t_data *data)
{
	data->forks = sem_open("forks", O_CREAT, 777, data->num_of_ph);
	data->printer = sem_open("printer", O_CREAT, 777, 1);
	if (data->forks == SEM_FAILED || data->printer == SEM_FAILED)
		data->rtn = ERROR_SEM_OPEN;
	sem_unlink("forks");
	sem_unlink("printer");
}

void	ft_init(int argc, char **argv, t_data *data)
{
	data->rtn = ft_args_check(argc, argv);
	if (!data->rtn)
	{
		data->num_of_ph = ft_atoi(argv[1]);
		data->time_to_die = ft_atoi(argv[2]);
		data->time_to_eat = ft_atoi(argv[3]);
		data->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			data->num_of_eats = ft_atoi(argv[5]);
		else
			data->num_of_eats = -1;
		data->still_hungry = data->num_of_ph;
		data->someone_died = 0;
		gettimeofday(&data->simulation_start_time, 0);
		data->last_meal_start_time = data->simulation_start_time;
	}
	if (!data->num_of_ph || !data->time_to_die
		|| !data->time_to_eat || !data->time_to_sleep)
		data->rtn = ERROR_INCORRECT_PARAMETERS;
}

pid_t	ft_invite_ph(t_data *data)
{
	pid_t	pid_rtn;

	pid_rtn = fork();
	if (pid_rtn == -1)
	{
		data->rtn = ERROR_CREATE_FORK;
		return (-1);
	}
	else if (!pid_rtn)
		_exit(ft_routine(data));
	else
		return (pid_rtn);
}

int	ft_identify_ph(pid_t *ph_pid, int pid)
{
	int	i;

	i = 0;
	while (ph_pid[i])
	{
		if (ph_pid[i] == pid)
			return (i + 1);
		i++;
	}
	return (SUCCESS);
}

void	ft_kill_all(t_data *data, pid_t *ph_pid)
{
	int	i;

	i = 0;
	while (i < data->num_of_ph)
	{
		kill(ph_pid[i], SIGKILL);
		i++;
	}
}
