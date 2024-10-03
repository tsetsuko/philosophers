/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:21 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/03 14:46:57 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_checker_s(t_monitor *m, t_philo *philo, long beginning)
{
	long	now_time;

	timestamp(beginning, &now_time);
	if (m->die <= now_time)
	{
		state_message(DIE, philo);
		m->end_flag = true;
	}
	return (1);
}

void	single_philo_routine(t_monitor *m, t_philo *p)
{
	safe_mutex_functions(LOCK, p->first_fork);
	state_message(F_FORK, p);
	philo_sleep(p, m->die);
	death_checker_s(m, p, m->beginning);
	safe_mutex_functions(UNLOCK, p->first_fork);
}

void	state_message(t_state state, t_philo *p)
{
	long	ms;
	long	beginning;

	if (get_bool(&p->monitor->end_flag, &p->monitor->end_lock) == true)
		return ;
	safe_mutex_functions(LOCK, p->write_lock);
	beginning = get_long(&p->monitor->beginning, &p->monitor->lock_long_var);
	timestamp(beginning, &ms);
	if (state == SLEEP)
		printf("%ldms %d is sleeping\n", ms, p->index);
	else if (state == EAT)
		printf("%ldms %d is eating\n", ms, p->index);
	else if (state == DIE)
		printf("%ldms %d died\n", ms, p->index);
	else if (state == S_FORK)
		printf("%ldms %d has taken second fork\n", ms, p->index);
	else if (state == F_FORK)
		printf("%ldms %d has taken first fork\n", ms, p->index);
	else if (state == THINK)
		printf("%ldms %d is thinking\n", ms, p->index);
	else
		error("wrong enum for the state message\n");
	safe_mutex_functions(UNLOCK, p->write_lock);
}

void	*routine(void *data)
{
	int			i;
	t_philo		*p;

	i = 0;
	p = (t_philo *)data;
	safe_mutex_functions(LOCK, p->last_meal_lock);
	// p->last_meal_time = get_long(&p->monitor->beginning,
	// 		&p->monitor->lock_long_var);
	safe_mutex_functions(UNLOCK, p->last_meal_lock);
	while (get_bool(&p->monitor->end_flag, &p->monitor->end_lock) == false)
	{
		philo_eat(p->monitor, p);
		if (get_bool(&p->monitor->end_flag, &p->monitor->end_lock) == true)
			break ;
		philo_sleep(p, get_long(&p->monitor->sleep,
				&p->monitor->lock_long_var));
		if (get_bool(p->end_flag, p->end_lock) == true)
			break ;
		philo_think(p);
	}
	return (NULL);
}
