/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 11:30:21 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 11:34:21 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

long int	get_time(void)
{
	long int		timestamp_in_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	timestamp_in_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (timestamp_in_ms);
}

long int	get_time_in_process(t_info *info)
{
	long int	tmp;
	long int	new_tmp;

	tmp = get_time();
	new_tmp = tmp - info->time_in_process;
	return (new_tmp);
}

void	atitude_philo(t_philo *philo, long int time, int id, int atitude)
{
	pthread_mutex_lock(&philo->info->mutex_is_dead);
	if (philo->info->is_dead == 0)
	{
		pthread_mutex_lock(&philo->info->mutex_write);
		if (atitude == 1)
			printf("%ld %d has taken a fork\n", time, id);
		else if (atitude == 2)
			printf("%ld %d is eating\n", time, id);
		else if (atitude == 3)
			printf("%ld %d is sleeping\n", time, id);
		else if (atitude == 4)
			printf("%ld %d is thinking\n", time, id);
		else if (atitude == 5)
			printf("%ld %d died\n", time, id);
		pthread_mutex_unlock(&philo->info->mutex_write);
	}
	pthread_mutex_unlock(&philo->info->mutex_is_dead);
}

void	my_usleep(long int timetosleep)
{
	long int	start;
	long int	actual_time;
	long int	end;

	start = get_time();
	end = start + timetosleep;
	while (1)
	{
		actual_time = get_time();
		if (actual_time >= end)
			break ;
		usleep(100);
	}
}
