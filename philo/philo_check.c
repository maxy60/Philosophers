/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:17:50 by msainton          #+#    #+#             */
/*   Updated: 2022/04/12 15:34:13 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	alive(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->info->n_philo)
	{
		if ()
	}
}

int create_check_thread()
{
	pthread_t	check;

	if (pthread_create(&check, NULL, &alive, &check) != 0)
		return (-1);
}
