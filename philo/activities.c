/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/11 18:35:59 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_monitor *m, t_philo *p)
{
	// printf(YELLOW"index[%d] entered philo eat\n"RST, p->index);
	// printf(RST);
	if (get_bool(&p->monitor->end_flag, &p->monitor->end_lock) == true)
		return	;
	safe_mutex_functions(LOCK, p->first_fork);
	state_message(F_FORK, p);
	safe_mutex_functions(LOCK, p->second_fork);
	state_message(S_FORK, p);
	if (get_bool(&p->monitor->end_flag, &p->monitor->end_lock) == true)
		return	;
	state_message(EAT, p);
	set_long(&p->last_meal_time, get_ms(), p->last_meal_lock);
	set_bool(&p->eating, true, p->lock_bool);
	// timestamp(get_long(&m->beginning, &m->lock_long_var), &p->last_meal_time);
	// printf("last meal time :%ld\n", get_long(&p->last_meal_time, p->last_meal_lock));
	usleep(m->time_of_eating * 1000);
	if (m->meal_counter == true)
	{
		safe_mutex_functions(LOCK, &m->lock_long_var);
		p->meal_counter++;
		safe_mutex_functions(UNLOCK, &m->lock_long_var);
	}
	safe_mutex_functions(UNLOCK, p->first_fork);
	safe_mutex_functions(UNLOCK, p->second_fork);
	set_bool(&p->eating, false, p->lock_bool);
}
