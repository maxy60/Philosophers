/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/15 16:53:29 by msainton         ###   ########.fr       */
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
		printf("[%ld] philo[%d] has taken a fork\n", get_time_in_process(philo->info), philo->id);
		return ;
	}
	if (philo->id % 2 == 0)
		usleep(10000);
	pthread_mutex_lock(&philo->forks[philo->id - 1]);
	pthread_mutex_lock(&philo->forks[philo->id]);
	printf("[%ld] philo[%d] has taken a fork\n", get_time_in_process(philo->info), philo->id);	
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
	if (philo[philo->id].ate == 1 && get_time_in_process(philo->info) <= philo[philo->id].death)
	{
		philo[philo->id].ate = 0;
		philo[philo->id].death += philo->info->time_to_die;
		return (1);
	}
	else if (philo[philo->id].ate == 0 && get_time_in_process(philo->info) <= philo[philo->id].death)
		return (1);
	printf("[%ld] death philo[%d] = %d\n", get_time_in_process(philo->info), philo->id, philo[philo->id].death);
	join_mythread(philo, philo->info->n_philo);
	return (0);
}

void	check_death(t_philo *philo)
{
	while (1)
	{
		if (check_meal(philo) == 0)
			break ;
	}
	philo->is_dead = 1;
	printf("JE SUIS ICI\n");
}

void	eat(t_philo *philo)
{
		take_fork(philo);
		pthread_mutex_lock(&philo->info->meal);
		philo[philo->id].ate++;
		pthread_mutex_unlock(&philo->info->meal);
		printf("[%ld] philo[%d] is eating\n", get_time_in_process(philo->info), philo->id);
		usleep((philo->info->time_to_eat * 1000));
		drop_fork(philo);
}

void	dodo(t_philo *philo)
{
		usleep(philo->info->time_to_sleep * 1000);
		printf("[%ld] philo[%d] is sleeping\n", get_time_in_process(philo->info), philo->id);
}

void	*routine(void *cast)
{
	t_philo *philo;

	philo = (t_philo *)cast;
	while (philo->is_dead != 1)
	{
		eat(philo);
		dodo(philo);
	}
	return (0);
}
