/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 14:58:00 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 16:04:00 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_eat(t_philosopher *ph)
{
	pthread_mutex_lock(ph->left_fork);
	pthread_mutex_lock(ph->right_fork);
	if (!ph->status->someone_died)
		printf("%ld %d has taken a fork\n",
			ft_time_since(ph->status->simulation_start_time),
			ph->id);
	gettimeofday(&ph->last_meal_start_time, 0);
	if (!ph->status->someone_died)
		printf("%ld %d is eating\n",
			ft_time_since(ph->status->simulation_start_time),
			ph->id);
	usleep(ph->data.time_to_eat * 1000);
	pthread_mutex_unlock(ph->right_fork);
	pthread_mutex_unlock(ph->left_fork);
	ph->data.num_of_eats--;
}

static void	ft_sleep(t_philosopher *ph)
{
	if (!ph->status->someone_died && ph->status->still_hungry)
	{
		printf("%ld %d is sleeping\n",
			ft_time_since(ph->status->simulation_start_time),
			ph->id);
		usleep(ph->data.time_to_sleep * 1000);
	}
	if (!ph->status->someone_died && ph->status->still_hungry)
	{
		printf("%ld %d is thinking\n",
			ft_time_since(ph->status->simulation_start_time),
			ph->id);
	}
}

void	*ft_routine(void *args)
{
	t_philosopher	*ph;

	ph = (t_philosopher *)args;
	while (!ph->status->someone_died && ph->data.num_of_eats)
	{
		ft_eat(ph);
		ft_sleep(ph);
	}
	return (SUCCESS);
}
