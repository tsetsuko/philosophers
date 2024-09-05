/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/03 16:03:37 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_monitor *m, t_philo *p)
{
	printf(YELLOW"index[%d] entered philo eat\n"RST, p->index);
	// printf(RST);
	safe_mutex_functions(LOCK, p->first_fork);
	state_message(F_FORK, p);
	safe_mutex_functions(LOCK, p->second_fork);
	state_message(S_FORK, p);
	set_bool(&p->eating, true, p->lock_bool);
	state_message(EAT, p);
	timestamp(get_long(&m->beginning, &m->lock_long_var), &p->last_meal_time);
	usleep(m->time_of_eating * 1000);
	set_bool(&p->eating, false, p->lock_bool);
	if (m->meal_counter == true)
		p->meal_counter++;
	safe_mutex_functions(UNLOCK, p->first_fork);
	safe_mutex_functions(UNLOCK, p->second_fork);
}
