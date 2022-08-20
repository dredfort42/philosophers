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

#include "philo_bonus.h"

static void	*ft_death_monitor(void *args)
{
	t_data	*data;

	data = (t_data *)args;
	while (data->num_of_eats)
	{
		if (ft_time_since(data->last_meal_start_time)
			> data->time_to_die)
			exit (DEATH);
		usleep(500);
	}
	return (SUCCESS);
}

static void	ft_eat(t_data *data)
{
	sem_wait(data->forks);
	sem_wait(data->forks);
	sem_wait(data->printer);
	printf("%ld %d has taken a fork\n",
		ft_time_since(data->simulation_start_time),
		data->ph_id);
	sem_post(data->printer);
	gettimeofday(&data->last_meal_start_time, 0);
	sem_wait(data->printer);
	printf("%ld %d is eating\n",
		ft_time_since(data->simulation_start_time),
		data->ph_id);
	sem_post(data->printer);
	usleep(data->time_to_eat * 1000);
	sem_post(data->forks);
	sem_post(data->forks);
	data->num_of_eats--;
}

static void	ft_sleep(t_data *data)
{
	sem_wait(data->printer);
	printf("%ld %d is sleeping\n",
		ft_time_since(data->simulation_start_time),
		data->ph_id);
	sem_post(data->printer);
	usleep(data->time_to_sleep * 1000);
	sem_wait(data->printer);
	printf("%ld %d is thinking\n",
		ft_time_since(data->simulation_start_time),
		data->ph_id);
	sem_post(data->printer);
}

char	ft_routine(t_data *data)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, 0, ft_death_monitor, (void *)data))
		return (ERROR_THREAD_CREATE);
	while (data->num_of_eats)
	{
		ft_eat(data);
		ft_sleep(data);
	}
	pthread_join(monitor, 0);
	return (SUCCESS);
}
