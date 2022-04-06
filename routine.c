/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/06 13:55:47 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

//pthread_mutex_t	meal;

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(philo->meal);
	int	i;

	i = 0;
	while (i <= philo->info->n_philo)
	{
		printf("PHILOOOO %d\n", philo->info->n_philo);
		printf("philo: is eating %d\n", i);
		i++;
	}
	pthread_mutex_unlock(philo->meal);
	return (0);
}
