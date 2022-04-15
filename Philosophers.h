/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:15 by msainton          #+#    #+#             */
/*   Updated: 2022/04/15 16:40:17 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_info
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		time_in_process;
	int				n_of_times_philo_eat;
	pthread_mutex_t	meal;
	struct	s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	int				ate;
	int				death;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	t_info			*info;
}	t_philo;

/** function lib    **/
int			ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr(int n);

/**  function parse   **/
int			check_if_number(char *str);
int			check_max(char *str);
long int	get_time();
long int	get_time_in_process();

/**  function init **/
void		init_info(t_info *info, char **argv);
void		init_philo_fork(t_info *info);
int			create_threads_inpair(t_philo *philo, int n_philo);
int			create_threads_pair(t_philo *philo, int n_philo);
int			join_mythread(t_philo *philo, int n_philo);

/**  routine **/
void		*routine();
void		*routine1();
int			check_meal(t_philo *philo);
void		check_death(t_philo *philo);

int			main(int argc, char **argv);

#endif
