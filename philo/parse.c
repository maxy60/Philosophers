/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 10:13:09 by msainton          #+#    #+#             */
/*   Updated: 2022/04/30 12:11:10 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

int	check_if_number(char *str)
{
	int	a;

	a = 0;
	while (str[a])
	{
		if ((str[a] < '0' || str[a] > '9') && str[a] != '+' && str[a] != '-')
			return (0);
		a++;
	}
	if (a > 10)
		return (0);
	return (1);
}

int	check_max(char *str)
{
	long int	i;

	if (check_if_number(str) == 1)
		i = ft_atoi(str);
	else
		return (-1);
	if (i > 2147483647 || i < -2147483648)
		return (-1);
	return ((int)i);
}

int	init_info(t_info *info, char **argv)
{
	if (check_max(argv[1]) <= 0 || check_max(argv[1]) == -1
		|| check_max(argv[2]) == -1 || check_max(argv[3]) == -1
		|| check_max(argv[4]) == -1)
		return (-1);
	info->is_dead = 0;
	info->as_eat = 0;
	info->time_in_process = get_time();
	info->n_philo = check_max(argv[1]);
	info->time_to_die = check_max(argv[2]);
	info->time_to_eat = check_max(argv[3]);
	info->time_to_sleep = check_max(argv[4]);
	if (argv[5] && check_max(argv[5]) != -1)
		info->n_of_times_philo_eat = check_max(argv[5]);
	else
		info->n_of_times_philo_eat = -1;
	return (0);
}
