/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:13:09 by msainton          #+#    #+#             */
/*   Updated: 2022/04/08 16:39:54 by msainton         ###   ########.fr       */
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
	info->time_in_process = get_time();
	info->n_philo = check_max(argv[1]);
	info->time_to_die = check_max(argv[2]);
	info->time_to_eat = check_max(argv[3]);
	info->time_to_sleep = check_max(argv[4]);
	if (argv[5])
		info->n_of_times_philo_eat = check_max(argv[5]);
}

#include <stdio.h>
long int	get_time()
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
	printf("new tmp = %ld\ninfo->timeproc = %ld\ntmp: %ld\n", new_tmp, info->time_in_process, tmp);
	return (tmp);
}
