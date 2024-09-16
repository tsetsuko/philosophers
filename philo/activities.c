/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:47 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/16 14:34:11 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_monitor *m, t_philo *p)
{
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
void	philo_think(t_philo *p)
{
	long	now;

	now = get_ms();
	state_message(THINK, p);
	while (p->time_to_think > get_ms() - now)
	{
		if (get_bool(p->end_flag, p->end_lock))
			break ;
		usleep(100);
	}
}
// this function will provide sleep for the philo but it will also check
// if the simulation hasn't stopped in the meanwhile
void	philo_sleep(t_philo *p, long time)
{
	// long	wake_up;
	long	now;

	state_message(SLEEP, p);
	now = get_ms();
	while (time > get_ms() - now)
	{
		if (get_bool(p->end_flag, p->end_lock))
			break ;
		usleep(100);
	}
}