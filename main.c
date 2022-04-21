/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/04/15 16:41:39 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

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
		pthread_mutex_init(&info.meal, NULL);
		create_threads_inpair(info.philo, info.n_philo);
		create_threads_pair(info.philo, info.n_philo);
		check_death(&info);
		pthread_mutex_destroy(&info.meal);
		join_mythread(info.philo, info.n_philo);
		free(info.philo);
	}
	else
		ft_putstr_fd("Error: wrong number of argument", 2);
}
