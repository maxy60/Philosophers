/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 10:40:16 by msainton          #+#    #+#             */
/*   Updated: 2022/03/31 16:35:39 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"



void	*routine(t_info *info)
{
	int i;

	i = 0;
	while (i < info->n_philo)
	{
		printf("philo pair %d\n", i);
		i++;
	}
	return (0);
}

void	*routine1(t_info *info)
{
	int i;

	i = 0;
	while (i < info->n_philo)
	{
		printf("philo inpair %d\n", i);
		i++;
	}
	return (0);
}
