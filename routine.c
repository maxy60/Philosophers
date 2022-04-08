/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/08 16:35:17 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	take_fork(t_philo *philo)
{
	printf("id %d\n", philo->id);
	if (philo->id == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		pthread_mutex_lock(&philo->forks[philo->info->n_philo - 1]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->forks[philo->id]);
	}
}

void	drop_fork(t_philo *philo)
{
	printf("id unlock %d\n", philo->id);
	if (philo->id == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id]);
		pthread_mutex_unlock(&philo->forks[philo->info->n_philo - 1]);
	}
	else if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id]);
	}
}

void	*routine(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->meal);
	get_time_in_process(philo->info);
	usleep(100000);
	printf("take my fork [%d] \n",philo->id);
	printf("take fork of  [%d]  \n",philo->id - 1);
	pthread_mutex_unlock(&philo->meal);
	drop_fork(philo);
	return (0);
}
