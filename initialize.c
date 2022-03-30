/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:52:36 by msainton          #+#    #+#             */
/*   Updated: 2022/03/30 17:01:15 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include <pthread.h>
#include <stdlib.h>

/*void	routine(t_info *info)
{
	if (info->philo->time_eat == info->time_to_eat)
	{
		
	}
}*/

void    init_philo_fork(t_info *info)
{
	pthread_mutex_t *forks;
	int	i;
	
	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * info->n_philo);
	if (!forks)
		return ;
	info->philo = malloc(sizeof(t_philo) * info->n_philo);
	if (!info->philo)
		return ;

	//pthread_create(&info->philo->thread, NULL, &routine, NULL);

	while (i <= info->n_philo)
	{
		info->philo[i].id = i + 1;
		i++;
	}
}