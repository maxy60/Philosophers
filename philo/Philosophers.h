/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:15 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 11:49:22 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_info
{
	int				n_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long int		time_in_process;
	int				n_of_times_philo_eat;
	pthread_mutex_t	mutex_is_dead;
	int				is_dead;
	int				as_eat;
	pthread_mutex_t	mutex_write;
	struct s_philo	*philo;
}	t_info;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	mutex_last_eat;
	int				last_eat;
	pthread_mutex_t	mutex_n_eat;
	int				n_eat;
	pthread_t		thread;
	pthread_mutex_t	*forks;
	t_info			*info;
}	t_philo;

/** function lib    **/
long int	ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnbr(int n);

/**  function parse   **/
int			check_if_number(char *str);
int			check_max(char *str);
long int	get_time(void);
long int	get_time_in_process(t_info *info);
void		atitude_philo(t_philo *philo, long int time, int id, int atitude);
void		my_usleep(long int timetosleep);

/** function forks **/
void		take_fork(t_philo *philo);
void		drop_fork(t_philo *philo);

/**  function init **/
int			init_info(t_info *info, char **argv);
void		init_philo_fork(t_info *info);
int			create_threads(t_philo *philo, int n_philo);
int			join_mythread(t_philo *philo, int n_philo);

/**  routine **/
void		*routine(void *cast);
int			check_meal(t_info *info, int i);
void		check_death(t_info *info);

int			main(int argc, char **argv);

#endif
