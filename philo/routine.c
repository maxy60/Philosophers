/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/26 10:26:27 by msainton         ###   ########.fr       */
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
		atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(10000);
	pthread_mutex_lock(&philo->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->forks[philo->id]);
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);	
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

int	check_meal(t_info *info, int i)
{
	if (get_time_in_process(info) <= info->philo[i].last_eat + info->time_to_die)
		return (1);
	atitude_philo(info->philo, get_time_in_process(info), info->philo[i].id, 5);
	info->is_dead = 1;
	return (0);
}

void	check_death(t_info *info)
{
	int i;
	int	stop;
	
	stop = 0;	
	while (stop != 1)
	{
		i = 0;
		while (i < info->n_philo)
		{
			if (check_meal(info, info->philo[i].id) == 0)
			{
				stop = 1;
				break ;
			}
			i++;
		}
	}
}

void	eat(t_philo *philo)
{
	if (philo->info->is_dead == 1)
			return ;
	take_fork(philo);
	pthread_mutex_lock(&philo->mutex_eat);
	philo->eat++;
	pthread_mutex_unlock(&philo->mutex_eat);
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 2);
	usleep((philo->info->time_to_eat * 1000));
	philo->last_eat = get_time_in_process(philo->info);
	pthread_mutex_lock(&philo->mutex_eat);
	philo->eat--;
	pthread_mutex_unlock(&philo->mutex_eat);
	drop_fork(philo);
}

void	dodo(t_philo *philo)
{

	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 3);
	usleep(philo->info->time_to_sleep * 1000);
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 4);
}

void	*routine(void *cast)
{
	t_philo *philo;

	philo = (t_philo *)cast;
	while (philo->info->is_dead != 1)
	{
		eat(philo);
		dodo(philo);
	}
	return (0);
}
