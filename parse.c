/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:13:09 by msainton          #+#    #+#             */
/*   Updated: 2022/03/30 17:01:00 by msainton         ###   ########.fr       */
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
	
	check_if_number(str);
	i = ft_atoi(str);
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