/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:13:09 by msainton          #+#    #+#             */
/*   Updated: 2022/04/07 12:54:45 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int check_if_number(char *str)
{
    int a;

    a = 0;
    while (str[a])
    {
        if (str[a] < '0' && str[a] > '9' && str[a] != '+' && str[a] != '-')
            return(0);
        a++;
    }
    if (a > 10)
        return (0);
    return (1);
}

int check_max(char *str)
{
	long int i;
	
	if (check_if_number(str) == 1)
		i = ft_atoi(str);
	else
		return (-1);
	if (i > 2147483647 || i < -2147483648)
		return (0);
	return ((int)i);
}

void	init_info(t_info *info, char **argv)
{
	info->n_philo = check_max(argv[1]);
	info->time_to_die = check_max(argv[2]);
	info->time_to_eat = check_max(argv[3]);
	info->time_to_sleep = check_max(argv[4]);
	if (argv[5])
		info->n_of_times_philo_eat = check_max(argv[5]);
}

#include <stdio.h>
int	get_time()
{
	int				timestamp_in_ms;
	struct timeval time;
	
	gettimeofday(&time, NULL);
	timestamp_in_ms = time.tv_usec / 1000;
	printf("time : %d\n",timestamp_in_ms);
	return (timestamp_in_ms);
}