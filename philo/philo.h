/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h       	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dredfort <dredfort@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 18:29:57 by dredfort          #+#    #+#             */
/*   Updated: 2021/12/29 15:47:46 by dredfort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define SUCCESS 0
# define ERROR_INPUT_PARAMETERS 1
# define ERROR_INCORRECT_PARAMETERS 2
# define ERROR_MALLOC_FORKS 11
# define ERROR_MALLOC_PHILOSOPHERS 12
# define ERROR_FORK_MUTEX_INIT 21
# define ERROR_THREAD_CREATE 31
# define ERROR_THREAD_JOIN 32

typedef struct s_options
{
	int	num_of_ph;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_of_eats;
}		t_options;

typedef struct s_status
{
	int				still_hungry;
	char			someone_died;
	int				body;
	long			time_of_death;
	struct timeval	simulation_start_time;
}					t_status;

typedef struct s_philosopher
{
	pthread_t		t;
	int				id;
	t_options		data;
	t_status		*status;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct timeval	last_meal_start_time;
}					t_philosopher;

//utilities
int				ft_atoi(const char *str);
char			ft_args_check(int argc, char **argv);
long			ft_time_since(struct timeval start_time);
void			ft_free_forks(int i, pthread_mutex_t	*forks);

//inits
void			ft_init_options(int argc, char **argv, t_options *options,
					char *rtn);
t_status		ft_init_status(struct s_options options);
pthread_mutex_t	*ft_init_forks(t_options options, char *rtn);
t_philosopher	*ft_init_philosophers(t_options options,
					pthread_mutex_t *forks,
					t_status *status,
					char *rtn);

//routine
void			*ft_routine(void *args);

//monitors
void			*ft_death_monitor(void *args);
void			*ft_hungry_monitor(void *args);
char			ft_monitoring(t_philosopher *ph);

#endif
