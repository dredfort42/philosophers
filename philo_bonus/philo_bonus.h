/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.h 	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 18:29:57 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:47:46 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/time.h>

# define SUCCESS 0
# define ERROR_MALLOC 1
# define ERROR_INCORRECT_PARAMETERS 2
# define ERROR_CREATE_FORK 11
# define ERROR_SEM_OPEN 21
# define ERROR_THREAD_CREATE 31
# define DEATH 888

typedef struct s_data
{
	char			rtn;
	int				ph_id;
	int				num_of_ph;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_eats;
	int				still_hungry;
	char			someone_died;
	struct timeval	simulation_start_time;
	struct timeval	last_meal_start_time;
	sem_t			*forks;
	sem_t			*printer;
}					t_data;

//utilities
int		ft_atoi(const char *str);
char	ft_args_check(int argc, char **argv);
long	ft_time_since(struct timeval start_time);

//inits
void	ft_init(int argc, char **argv, t_data *data);
void	ft_sems_open(t_data *data);
pid_t	ft_invite_ph(t_data *data);
int		ft_identify_ph(pid_t *ph_pid, int pid);
void	ft_kill_all(t_data *data, pid_t *ph_pid);

//routine
char	ft_routine(t_data *data);
#endif
