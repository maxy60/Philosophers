/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:47:15 by msainton          #+#    #+#             */
/*   Updated: 2022/03/30 16:55:02 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <pthread.h>
#include <unistd.h>

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
	int			id;
	int			time_eat;
	pthread_t	thread;
}	t_philo;

/** function lib    **/
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);

/**  function parse   **/
int		check_if_number(char *str);
int		check_max(char *str);

/**  function init **/
void	init_info(t_info *info, char **argv);
void	init_philo_fork(t_info *info);

int		main(int argc, char **argv);

#endif