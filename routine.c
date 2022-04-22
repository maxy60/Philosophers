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

int	check_meal(t_philo *philo, int i)
{
	if (get_time_in_process(philo->info) <= philo[i].death && philo->ate == 1)
	{
		philo->ate = 0;
		philo[i].death += philo->info->time_to_die;
		return (1);
	}
	if (get_time_in_process(philo->info) <= philo[i].death)
		return (1);
	printf("[%ld] death philo[%d] = %d\n", get_time_in_process(philo->info), philo->id, philo[i].death);
	philo->info->is_dead = 1;
	join_mythread(philo, philo->info->n_philo);
	return (0);
}

int	check_death(t_philo *philo)
{
	//while (1)
	//{
	if (check_meal(philo, philo->id) == 1)
		return (0);
	//		break ;
	//}
	printf("is_dead = %d philo[%d] have to death at %d, time in process %ld\n",philo->info->is_dead, philo->id, philo->death, get_time_in_process(philo->info));
	return(1);
}

void	eat(t_philo *philo)
{
		if (philo->info->is_dead == 1)
			return ;
		take_fork(philo);
		pthread_mutex_lock(&philo->info->meal);
		philo->ate++;
		pthread_mutex_unlock(&philo->info->meal);
		printf("[%ld] philo[%d] is eating\n", get_time_in_process(philo->info), philo->id);
		usleep((philo->info->time_to_eat * 1000));
		drop_fork(philo);
}

void	dodo(t_philo *philo)
{
		//int time_thinking;

		if (philo->info->is_dead == 1)
			return ;
		usleep(philo->info->time_to_sleep * 1000);
		printf("[%ld] philo[%d] is sleeping\n", get_time_in_process(philo->info), philo->id);
		/*time_thinking = philo->info->time_to_sleep + (get_time_in_process(philo->info) - philo->death) < philo->death;
		if (time_thinking < philo->death)
		{
			usleep(time_thinking);
			printf("[%ld] philo[%d] is thinking\n", get_time_in_process(philo->info), philo->id);
		}
		int think = philo->info->time_to_sleep + get_time_in_process(philo->info) - philo->death;
		printf("[%d] think = %d  death = %d\n", philo->id, think, philo->death);
*/
}

void	*routine(void *cast)
{
	t_philo *philo;

	philo = (t_philo *)cast;
	while (check_death(philo) == 0)
	{
		eat(philo);
		dodo(philo);
	}
	return (0);
}
