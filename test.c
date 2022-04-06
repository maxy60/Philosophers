/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msainton <msainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:59:37 by msainton          #+#    #+#             */
/*   Updated: 2022/04/06 16:42:56 by msainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

//pthread_mutex_t mutex;

void	*routine()
{
	int i = 0;
	
	
	printf("thread\n");
	//pthread_mutex_lock(&mutex);
	while (i < 100000000)
	{
		i++;
		printf("i = %d\n", i);
	}
	//pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, &routine, NULL);
	pthread_create(&t2, NULL, &routine, NULL);
	pthread_create(&t3, NULL, &routine, NULL);
	pthread_create(&t4, NULL, &routine, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
}