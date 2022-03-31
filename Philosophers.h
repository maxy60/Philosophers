/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:15 by msainton          #+#    #+#             */
/*   Updated: 2022/03/31 13:40:12 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_info
{
	int		n_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		n_of_times_philo_eat;
	struct	s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*forks;
}	t_philo;

/** function lib    **/
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

/**  function parse   **/
int		check_if_number(char *str);
int		check_max(char *str);
int		get_time();

/**  function init **/
void	init_info(t_info *info, char **argv);
void	init_philo_fork(t_info *info);
int		create_threads_even(t_philo *philo, int n_philo);
int		create_threads_odd(t_philo *philo, int n_philo);
int		join_mythread(t_philo *philo, int n_philo);

/**  routine **/
void	*routine();
void	*routine1();

int		main(int argc, char **argv);

#endif