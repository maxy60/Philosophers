/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:52:36 by msainton          #+#    #+#             */
/*   Updated: 2022/04/29 13:14:19 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
#include <pthread.h>
#include <stdlib.h>

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
	while (i < info->n_philo)
	{
		info->philo[i].id = i;
		info->philo[i].eat = 0;
	//	if (info->n_of_times_philo_eat)
	//		info->philo[i].n_eat = 0;
		info->philo[i].last_eat = 0;
		info->philo[i].forks = forks;
		info->philo[i].info = info;
		pthread_mutex_init(&info->philo[i].mutex_last_eat, NULL);
		pthread_mutex_init(&info->philo[i].mutex_eat, NULL);
		pthread_mutex_init(&info->philo[i].forks[i], NULL);
		i++;
	}
}

int	create_threads_pair(t_philo *philo, int n_philo)
{
	int	i;
	
	i = 0;
	while (i <= n_philo - 1)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i += 2;
		
	}
	return (0);
}

int	create_threads_inpair(t_philo *philo, int n_philo)
{
	int	i;
	
	i = 1;
	while (i <= n_philo - 1)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			return (-1);
		i += 2;
		
	}
	return (0);
}

int create_threads(t_philo *philo, int n_philo)
{
	if (create_threads_inpair(philo, n_philo))
		return (-1);
	usleep(100);
	if (create_threads_pair(philo, n_philo))
		return (-1);
	check_death(philo->info);
	join_mythread(philo, philo->info->n_philo);
	return (0);
}

int	join_mythread(t_philo *philo, int n_philo)
{
	int	i;

	i = 0;
	while (i < n_philo)
	{
		if  (pthread_join(philo[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
