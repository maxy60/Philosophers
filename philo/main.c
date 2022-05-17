/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/05/17 11:10:49 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	destroy_mutex(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&info->philo[i].mutex_last_eat);
		pthread_mutex_destroy(&info->philo[i].mutex_n_eat);
		pthread_mutex_destroy(&info->philo[i].forks[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		if (init_info(&info, argv) == -1)
		{
			ft_putstr_fd("Error: argument contain bad value", 2);
			return (-1);
		}
		init_philo_fork(&info);
		pthread_mutex_init(&info.mutex_write, NULL);
		pthread_mutex_init(&info.mutex_is_dead, NULL);
		create_threads(info.philo, info.n_philo);
		pthread_mutex_destroy(&info.mutex_write);
		pthread_mutex_destroy(&info.mutex_is_dead);
		destroy_mutex(&info);
		free(info.philo->forks);
		free(info.philo);
	}
	else
		ft_putstr_fd("Error: wrong number of argument", 2);
}
