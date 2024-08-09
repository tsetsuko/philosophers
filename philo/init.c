/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:55:00 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/09 22:43:10 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_info_dump(t_forks *fork, int i)
{
	printf("fork\n");
	pthread_mutex_t lock;

	fork->index = i + 1;
	pthread_mutex_init(&lock, NULL);
	fork->lock = lock;
}

void	philo_info_dump(t_monitor *m, t_philo *philo, int index, t_forks **forks)
{
	printf("philo\n");
	if (philo == NULL)
		printf("philo is null\n");
	if (m == NULL)
		printf("m is null\n");
	philo->monitor = m;
	printf("after\n");
	philo->index = index + 1;
	philo->position = index;
	philo->meal_counter = 0;
	philo->forks = forks;
	printf("after\n");
}