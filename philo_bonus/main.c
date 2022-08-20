/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c 	                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 13:09:00 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:51:00 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_waiting(t_data *data, pid_t *ph_pid)
{
	int	w_pid;
	int	pid_status;

	pid_status = 0;
	while (!data->someone_died && data->still_hungry)
	{
		w_pid = waitpid(-1, &pid_status, 0);
		if (!pid_status)
			data->still_hungry--;
		else
		{
			sem_wait(data->printer);
			printf("%ld %d died\n",
				ft_time_since(data->simulation_start_time),
				ft_identify_ph(ph_pid, w_pid));
			ft_kill_all(data, ph_pid);
			sem_post(data->printer);
			data->someone_died++;
		}
	}
}

static void	ft_simulation(t_data *data)
{
	pid_t	*ph_pid;
	int		i;

	ph_pid = malloc(sizeof(pid_t) * data->num_of_ph);
	if (!ph_pid)
		data->rtn = ERROR_MALLOC;
	i = 0;
	while (i < data->num_of_ph && !data->rtn)
	{
		usleep(500);
		data->ph_id = i + 1;
		ph_pid[i] = ft_invite_ph(data);
		i++;
	}
	ft_waiting(data, ph_pid);
	free(ph_pid);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	char	rtn;

	if (argc < 4 || argc > 6)
		return (ERROR_INCORRECT_PARAMETERS);
	data = malloc(sizeof(t_data));
	if (!data)
		return (ERROR_MALLOC);
	rtn = 0;
	ft_init(argc, argv, data);
	if (!data->rtn)
	{
		ft_sems_open(data);
		if (data->num_of_ph > 1)
			ft_simulation(data);
		else
			printf("%d 1 died\n", data->time_to_die);
		rtn = data->rtn;
		free(data);
	}
	return (rtn);
}
