/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/09 23:13:39 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_monitor *m, t_philo *p)
{
	if (!(p->index % 2))
	{
		p->first_fork = p->forks[p->position + 1];
		if (pthread_mutex_lock(&p->forks[(p->position + 1) % m->num_of_philos]->lock) == 0)
			state_message(m->beginning, F_FORK, p->index);
		p->second_fork = p->forks[p->position];
		if (pthread_mutex_lock(&p->forks[(p->position)]->lock) == 0)
			state_message(m->beginning, S_FORK, p->index);
	}
	else
	{
		p->first_fork = p->forks[p->position];
		if (pthread_mutex_lock(&p->forks[(p->position)]->lock) == 0)
			state_message(m->beginning, F_FORK, p->index);
		p->second_fork = p->forks[(p->position + 1) % m->num_of_philos];
		if (pthread_mutex_lock(&p->forks[(p->position + 1) % m->num_of_philos]->lock) == 0)
			state_message(m->beginning, S_FORK, p->index);
	}
	if (p->first_fork && p->second_fork)
	{
		state_message(m->beginning, EAT, p->index);
		timestamp(m->beginning, &p->last_meal_time);
		usleep(m->time_of_eating * 1000);
		if (m->meal_counter == true)
			p->meal_counter++;
		pthread_mutex_unlock(&p->forks[(p->position + 1) % m->num_of_philos]->lock);
		pthread_mutex_unlock(&p->forks[(p->position)]->lock);
	}
}
