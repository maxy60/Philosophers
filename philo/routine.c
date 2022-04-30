/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 11:55:41 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->mutex_is_dead);
	if (philo->info->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->info->mutex_is_dead);
		return ;
	}
	pthread_mutex_unlock(&philo->info->mutex_is_dead);
	take_fork(philo);
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 2);
	usleep((philo->info->time_to_eat * 1000));
	pthread_mutex_lock(&philo->mutex_n_eat);
	philo->n_eat++;
	pthread_mutex_unlock(&philo->mutex_n_eat);
	pthread_mutex_lock(&philo->mutex_last_eat);
	philo->last_eat = get_time_in_process(philo->info);
	pthread_mutex_unlock(&philo->mutex_last_eat);
	drop_fork(philo);
}

void	dodo(t_philo *philo)
{
	printf(" as eat %d time = %ld\n", philo->info->as_eat, get_time_in_process(philo->info));
	if (philo->info->as_eat == 1)
		return ;
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 3);
	usleep(philo->info->time_to_sleep * 1000);
	if (philo->info->as_eat == 1)
		return ;
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 4);
	if ((((philo->info->time_to_die - (philo->info->time_to_eat
						+ philo->info->time_to_sleep)) / 2) * 1000) > 0)
		usleep(((philo->info->time_to_die - (philo->info->time_to_eat
						+ philo->info->time_to_sleep)) / 2) * 1000);
}

void	one_philo_routine(t_philo *philo)
{
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
	usleep(philo->info->time_to_die * 1000);
	return ;
}

void	*routine(void *cast)
{
	t_philo	*philo;

	philo = (t_philo *)cast;
	if (philo->info->n_philo == 1)
	{
		one_philo_routine(philo);
		return (0);
	}
	while (philo->info->is_dead != 1 && philo->info->as_eat != 1)
	{
		eat(philo);
		dodo(philo);
	}
	return (0);
}
