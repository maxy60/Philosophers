/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:44:45 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 11:49:10 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_meal(t_info *info, int i)
{
	pthread_mutex_lock(&info->philo[i].mutex_last_eat);
	if (get_time_in_process(info)
		<= info->philo[i].last_eat + info->time_to_die)
	{
		pthread_mutex_unlock(&info->philo[i].mutex_last_eat);
		return (1);
	}
	pthread_mutex_unlock(&info->philo[i].mutex_last_eat);
	atitude_philo(info->philo, get_time_in_process(info), info->philo[i].id, 5);
	pthread_mutex_lock(&info->mutex_is_dead);
	info->is_dead = 1;
	pthread_mutex_unlock(&info->mutex_is_dead);
	return (0);
}

int	each_eat_philo(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info->n_philo)
	{
		if (info->philo[i].n_eat == info->n_of_times_philo_eat)
			j++;
		i++;
	}
	if (j == info->n_philo)
	{
		info->as_eat = 1;
		return (0);
	}
	return (1);
}

void	check_death(t_info *info)
{
	int	i;
	int	stop;

	stop = 0;
	while (stop != 1)
	{
		i = 0;
		while (i < info->n_philo)
		{
			if (each_eat_philo(info) == 0)
			{
				stop = 1;
				break ;
			}
			if (check_meal(info, info->philo[i].id) == 0)
			{
				stop = 1;
				break ;
			}
			i++;
		}
	}
}
