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

#include "philo.h"

void	ft_init_options(int argc, char **argv, t_options *options, char *rtn)
{
	*rtn = ft_args_check(argc, argv);
	if (!*rtn)
	{
		options->num_of_ph = ft_atoi(argv[1]);
		options->time_to_die = ft_atoi(argv[2]);
		options->time_to_eat = ft_atoi(argv[3]);
		options->time_to_sleep = ft_atoi(argv[4]);
		if (argv[5])
			options->num_of_eats = ft_atoi(argv[5]);
		else
			options->num_of_eats = -1;
	}
	if (!options->num_of_ph || !options->time_to_die
		|| !options->time_to_eat || !options->time_to_sleep)
		*rtn = ERROR_INCORRECT_PARAMETERS;
}

t_status	ft_init_status(struct s_options options)
{
	t_status	status;

	status.still_hungry = options.num_of_ph;
	status.someone_died = 0;
	status.time_of_death = 0;
	status.body = -1;
	gettimeofday(&status.simulation_start_time, 0);
	return (status);
}

pthread_mutex_t	*ft_init_forks(t_options options, char *rtn)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * options.num_of_ph);
	if (!forks)
	{
		*rtn = ERROR_MALLOC_FORKS;
		return (NULL);
	}
	i = 0;
	while (i < options.num_of_ph)
	{
		if (pthread_mutex_init(&forks[i], 0))
		{
			ft_free_forks(i, forks);
			*rtn = ERROR_FORK_MUTEX_INIT;
			return (NULL);
		}
		i++;
	}
	return (forks);
}

static void	ft_set_philosophers(t_philosopher *ph,
							t_options options,
							pthread_mutex_t *forks,
							t_status *status)
{
	int	i;

	i = 0;
	gettimeofday(&status->simulation_start_time, 0);
	while (i < options.num_of_ph)
	{
		ph[i].t = 0;
		ph[i].id = i + 1;
		ph[i].data = options;
		ph[i].status = status;
		ph[i].left_fork = &forks[i];
		if (i == options.num_of_ph - 1)
			ph[i].right_fork = &forks[0];
		else
			ph[i].right_fork = &forks[i + 1];
		ph[i].last_meal_start_time = status->simulation_start_time;
		i++;
	}
}

t_philosopher	*ft_init_philosophers(t_options options,
									pthread_mutex_t *forks,
									t_status *status,
									char *rtn)
{
	t_philosopher	*ph;

	ph = malloc(sizeof(t_philosopher) * options.num_of_ph);
	if (!ph)
	{
		*rtn = ERROR_MALLOC_PHILOSOPHERS;
		return (NULL);
	}
	ft_set_philosophers(ph, options, forks, status);
	return (ph);
}
