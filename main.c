/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:23:58 by msainton          #+#    #+#             */
/*   Updated: 2022/03/28 16:41:54 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	init_iphilo(t_iphilo *iphilo, char **argv)
{
	iphilo->n_philo = argv[1];
	iphilo->time_to_die = argv[2];
	iphilo->time_to_eat = argv[3];
	iphilo->time_to_sleep = argv[4];
	if (argv[5])
		iphilo->n_of_times_philo_eat = argv[5];
}

int	main(int argc, char **argv)
{
	t_iphilo	iphilo;

	if (argc == 5 || argc == 6)
	{
		init_philo(iphilo, argv);
	}
	else
		ft_putstr_fd("Error: wrong number of argument",2);
}
