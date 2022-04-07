/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/07 16:40:51 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	take_fork(t_philo *philo)
{
	printf("id %d\n", philo->id);
	if (philo->id % 2 == 0)
	{
		printf("id paire %d\n", philo->id);
		pthread_mutex_lock(&philo->forks[philo->id]);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
	}
	else
	{
		printf("id inpair %d\n", philo->id);
		pthread_mutex_lock(&philo->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->forks[philo->id]);
	}
}

void	drop_fork(t_philo *philo)
{
	printf("id unlock %d\n", philo->id);
	if (philo->id % 2 == 0)
	{
		printf("id paire unlock %d\n", philo->id);
		pthread_mutex_unlock(&philo->forks[philo->id]);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
	}
	else
	{
		printf("id inpair unlock %d\n", philo->id);
		pthread_mutex_unlock(&philo->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->forks[philo->id]);
	}
}

void	*routine(t_philo *philo)
{
	take_fork(philo);
	printf("je prend ma fourchette [%d] \n",philo->id);
	printf("et je prend ta fourchette fdp  [%d]  \n",philo->id - 1);
	drop_fork(philo);
	return (0);
}
