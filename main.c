/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/03/31 14:11:06 by msainton         ###   ########.fr       */
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
		//pthread_mutex_init(&mutex, NULL);
		create_threads_even(info.philo, info.n_philo);
		create_threads_odd(info.philo, info.n_philo);
		join_mythread(info.philo, info.n_philo);
		//pthread_mutex_destroy(&mutex);
	//	get_time();
	}
	else
		ft_putstr_fd("Error: wrong number of argument", 2);
}
