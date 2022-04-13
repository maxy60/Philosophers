/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/13 16:29:54 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	take_fork(t_philo *philo)
{
	if (philo->id == 0)
	{
		usleep(10000);
		pthread_mutex_lock(&philo->forks[philo->id]);
		pthread_mutex_lock(&philo->forks[philo->info->n_philo - 1]);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(10000);
	pthread_mutex_lock(&philo->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->forks[philo->id]);
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

int	check_meal(t_philo *philo)
{
	if (philo[philo->id].ate == 1 && get_time_in_process() <= philo[philo->id].death)
	{
		//printf("im here\n");
		philo[philo->id].ate = 0;
		philo[philo->id].death += philo->info->time_to_die;
		return (1);
	}
	return (0);
}

void	check_death(t_philo *philo)
{
	while (1)
	{
		if (check_meal(philo) == 0)
			break ;
	}
	printf("LE PHILO EST MORT TANTAN TAN TAN\n");
}

void	*routine(t_philo *philo)
{
	take_fork(philo);
	pthread_mutex_lock(&philo->meal);
	philo[philo->id].ate++;
	pthread_mutex_unlock(&philo->meal);
	printf("[%ld]  philo [%d] is eating\n", get_time_in_process(philo->info), philo->id);
	usleep((philo->info->time_to_eat * 1000));
	drop_fork(philo);
	return (0);
}
