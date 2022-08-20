/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitors.c    	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 13:09:00 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:51:00 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_death_monitor(void *args)
{
	t_philosopher	*ph;
	t_status		*status;
	int				i;

	ph = (t_philosopher *)args;
	status = ph[0].status;
	while (!status->someone_died && status->still_hungry)
	{
		i = 0;
		while (!status->someone_died && status->still_hungry
			&& i < ph[0].data.num_of_ph)
		{
			if (ft_time_since(ph[i].last_meal_start_time)
				> ph[0].data.time_to_die)
			{
				status->someone_died = 1;
				status->time_of_death
					= ft_time_since(status->simulation_start_time);
				status->body = i + 1;
			}
			i++;
		}
		usleep(2500);
	}
	return (SUCCESS);
}

void	*ft_hungry_monitor(void *args)
{
	t_philosopher	*ph;
	t_status		*status;
	int				i;
	int				s_hungry;

	ph = (t_philosopher *)args;
	status = ph[0].status;
	while (status->still_hungry && !status->someone_died)
	{
		i = 0;
		s_hungry = 0;
		while (status->still_hungry && !status->someone_died
			&& i < ph[0].data.num_of_ph)
		{
			s_hungry += ph[i].data.num_of_eats;
			i++;
		}
		status->still_hungry = s_hungry;
		usleep(2500);
	}
	return (SUCCESS);
}
