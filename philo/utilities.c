/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c 	                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 13:09:00 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:52:00 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char ch)
{
	if (ch == ' ' || ch == '\t' || ch == '\n'
		|| ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long int	num;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
		num = num * 10 + (str[i++] - '0');
	if (num < 0 && sign > 0)
		return (-1);
	else if (num < 0 && sign <= 0)
		return (0);
	else
		return (sign * (int)num);
}

char	ft_args_check(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc == 5 || argc == 6)
	{
		i = 1;
		while (i < argc)
		{
			j = 0;
			while (argv[i][j])
			{
				if ((argv[i][j] < '0' || argv[i][j] > '9') && argv[i][j] != '+')
					return (ERROR_INCORRECT_PARAMETERS);
				j++;
			}
			i++;
		}
		return (SUCCESS);
	}
	return (ERROR_INPUT_PARAMETERS);
}

long	ft_time_since(struct timeval start_time)
{
	struct timeval	current_time;
	struct timeval	delta_time;

	gettimeofday(&current_time, 0);
	delta_time.tv_sec = current_time.tv_sec - start_time.tv_sec;
	delta_time.tv_usec = current_time.tv_usec - start_time.tv_usec;
	if (delta_time.tv_usec < 0)
	{
		delta_time.tv_sec--;
		delta_time.tv_usec += 1000000;
	}
	return (delta_time.tv_sec * 1000 + delta_time.tv_usec / 1000);
}

void	ft_free_forks(int i, pthread_mutex_t	*forks)
{
	while (i >= 0)
	{
		pthread_mutex_destroy(&forks[i]);
		i--;
	}
	free(forks);
}
