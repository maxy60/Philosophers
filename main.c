/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/04/13 16:16:55 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		init_info(&info, argv);
		init_philo_fork(&info);
		pthread_mutex_init(&info.philo->meal, NULL);
		create_threads_odd(info.philo, info.n_philo);
		create_threads_even(info.philo, info.n_philo);
		check_death(info.philo);
		pthread_mutex_destroy(&info.philo->meal);
		join_mythread(info.philo, info.n_philo);
		free(info.philo);
	}
	else
		ft_putstr_fd("Error: wrong number of argument", 2);
}
