/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/12 14:56:34 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_monitor *m, t_philo *p)
{
	printf(YELLOW"index[%d] entered philo eat\n"RST, p->index);
	// printf(RST);

	if (!(p->index % 2))
	{
		if (pthread_mutex_lock(&p->forks[(p->position + 1) % m->num_of_philos]) == 0)
			state_message(m->beginning, F_FORK, p);
		else
			error("philo eat");
		if (pthread_mutex_lock(&p->forks[(p->position)]) == 0)
			state_message(m->beginning, S_FORK, p);
		else
			error("philo eat");
	}
	else
	{
		if (pthread_mutex_lock(&p->forks[p->position]) == 0)
			state_message(m->beginning, F_FORK, p);
		else
			error("philo eat");
		if (pthread_mutex_lock(&p->forks[(p->position + 1) % m->num_of_philos]) == 0)
			state_message(m->beginning, S_FORK, p);
		else
			error("philo eat");
	}
	p->eating = true;
	state_message(m->beginning, EAT, p);
	timestamp(m->beginning, &p->last_meal_time);
	usleep(m->time_of_eating * 1000);
	p->eating = false;
	if (m->meal_counter == true)
		p->meal_counter++;
	pthread_mutex_unlock(&p->forks[(p->position + 1) % m->num_of_philos]);
	pthread_mutex_unlock(&p->forks[(p->position)]);
}
