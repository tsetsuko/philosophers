/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:55:00 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/12 14:10:14 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_info_dump(pthread_mutex_t *fork)
{
	if (pthread_mutex_init(fork, NULL) == 0)
		printf("mutex fork created\n");
}

void	philo_info_dump(t_monitor *m, t_philo *philo, int index, pthread_mutex_t *forks)
{
	pthread_mutex_t write_message;
	pthread_mutex_t	meal_lock;

	if (pthread_mutex_init(&write_message, NULL) == 0)
		printf("write state lock ok\n");
	if (pthread_mutex_init(&meal_lock, NULL) == 0)
		printf("write state lock ok\n");
	philo->write_message = write_message;
	philo->last_meal_lock = meal_lock;
	philo->monitor = m;
	philo->index = index + 1;
	philo->position = index;
	philo->meal_counter = 0;
	philo->forks = forks;
}