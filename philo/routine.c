/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/04/29 13:46:00 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void    take_fork(t_philo *philo)
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

void    drop_fork(t_philo *philo)
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
	pthread_mutex_lock(&info->philo[i].mutex_last_eat);
	if (get_time_in_process(info) <= info->philo[i].last_eat + info->time_to_die)
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

int each_eat_philo(t_info *info)
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
	int i;
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
	//printf(" as eat %d time = %ld\n", philo->info->as_eat, get_time_in_process(philo->info));
	if (philo->info->as_eat == 1)
		return ;
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 3);
	usleep(philo->info->time_to_sleep * 1000);
	atitude_philo(philo, get_time_in_process(philo->info), philo->id, 4);
	if ((((philo->info->time_to_die - (philo->info->time_to_eat + philo->info->time_to_sleep)) / 2) * 1000) > 0)
		usleep(((philo->info->time_to_die - (philo->info->time_to_eat + philo->info->time_to_sleep)) / 2) * 1000);
}

void	one_philo_routine(t_philo *philo)
{
    atitude_philo(philo, get_time_in_process(philo->info), philo->id, 1);
	usleep(philo->info->time_to_die * 1000);
	return ;
}

void	*routine(void *cast)
{
	t_philo *philo;

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
