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

#include "philo.h"

char	ft_start(short num, t_options options, t_philosopher *ph)
{
	while (num < options.num_of_ph)
	{
		if (pthread_create(&ph[num].t, 0, ft_routine, (void *)
				&ph[num]))
			return (ERROR_THREAD_CREATE);
		num += 2;
	}
	return (SUCCESS);
}

char	ft_monitoring(t_philosopher *ph)
{
	pthread_t	death_monitor;
	pthread_t	hungry_monitor;

	death_monitor = 0;
	hungry_monitor = 0;
	if (pthread_create(&death_monitor, 0, ft_death_monitor, (void *)ph))
		return (ERROR_THREAD_CREATE);
	if (ph[0].data.num_of_eats > 0
		&& pthread_create(&hungry_monitor, 0, ft_hungry_monitor, (void *)ph))
		return (ERROR_THREAD_CREATE);
	if (pthread_join(death_monitor, 0))
		return (ERROR_THREAD_JOIN);
	if (ph[0].data.num_of_eats > 0
		&& pthread_join(hungry_monitor, 0))
		return (ERROR_THREAD_JOIN);
	return (SUCCESS);
}

void	ft_waiting(t_philosopher *ph, char *rtn)
{
	int	i;

	i = 0;
	while (i < ph[0].data.num_of_ph)
	{
		if (pthread_join(ph[i].t, 0))
			*rtn = (ERROR_THREAD_JOIN);
		i++;
	}
}

static void	ft_simulation(t_options options, char *rtn)
{
	t_status		status;
	pthread_mutex_t	*forks;
	t_philosopher	*ph;

	status = ft_init_status(options);
	forks = ft_init_forks(options, rtn);
	if (!*rtn)
	{
		ph = ft_init_philosophers(options, forks, &status, rtn);
		if (!*rtn)
		{
			gettimeofday(&status.simulation_start_time, 0);
			if (ft_start(0, options, ph) || ft_start(1, options, ph))
				*rtn = ERROR_THREAD_CREATE;
			if (ft_monitoring(ph))
				*rtn = ERROR_THREAD_CREATE;
			ft_waiting(ph, rtn);
			if (status.still_hungry && status.someone_died)
				printf("%ld %d died\n", status.time_of_death, status.body);
			free(ph);
		}
		ft_free_forks(options.num_of_ph - 1, forks);
	}
}

int	main(int argc, char **argv)
{
	char		rtn;
	t_options	options;

	rtn = SUCCESS;
	ft_init_options(argc, argv, &options, &rtn);
	if (!rtn)
	{
		if (options.num_of_ph > 1)
			ft_simulation(options, &rtn);
		else
			printf("%d 1 died\n", options.time_to_die);
	}
	return (rtn);
}
