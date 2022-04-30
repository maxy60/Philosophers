/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:45:59 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 11:46:24 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	take_fork(t_philo *philo)
{
	if (philo->id == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
		pthread_mutex_lock(&philo->forks[philo->info->n_philo - 1]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->id]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
		pthread_mutex_lock(&philo->forks[philo->id % philo->info->n_philo]);
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
	}
}

void	drop_fork(t_philo *philo)
{
	if (philo->id == 0)
	{
		pthread_mutex_unlock(&philo->forks[philo->id]);
		pthread_mutex_unlock(&philo->forks[philo->info->n_philo - 1]);
		return ;
	}
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_unlock(&philo->forks[philo->id - 1]);
}
