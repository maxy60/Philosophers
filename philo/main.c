/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/04/26 08:58:46 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"



void	destroy_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->n_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex_eat);
		pthread_mutex_destroy(&philo[i].mutex_last_eat);
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
		create_threads(info.philo, info.n_philo);
		pthread_mutex_destroy(&info.mutex_write);
		destroy_mutex(info.philo);
		free(info.philo);
	}
	else
		ft_putstr_fd("Error: wrong number of argument", 2);
}
