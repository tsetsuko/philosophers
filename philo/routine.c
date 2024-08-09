/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:21 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/09 23:22:11 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this function will provide sleep for the philo but it will also check
// if the simulation hasn't stopped in the meanwhile
void	philo_sleep(t_monitor *m, long time)
{
	// long	wake_up;
	long	now;

	now = get_ms();
	// wake_up = now + time;
	while (time > get_ms() - now)
	{
		if (m->end_flag)
		{
			printf("end\n");
			break ;
		}
		usleep(100);
	}
}

int	death_checker(t_monitor *m, t_philo *philo, long beginning)
{
	long	now_time;

	timestamp(beginning, &now_time);
	if (m->die <= now_time)
	{
		philo->death_flag = true;
		state_message(m->beginning, DIE, philo->index);
		m->end_flag = true;
		//end simulation
	}
	return (1);
}

void	single_philo_routine(t_monitor *m, t_philo *p)
{
	p->first_fork = p->forks[p->position];
	pthread_mutex_lock(&p->forks[p->position]->lock);
	state_message(m->beginning, F_FORK, p->index);
	philo_sleep(m, m->die);
	death_checker(m, p, m->beginning);
	pthread_mutex_unlock(&p->forks[p->position]->lock);
}

void	state_message(long beginning, t_state state, int index)
{
	long	ms;

	// ms = 
	// create a write lock
	timestamp(beginning, &ms);
	if (state == SLEEP)
		printf("%ldms %d is sleeping\n", ms, index);
	else if (state == EAT)
		printf("%ldms %d is eating\n", ms, index);
	else if (state == DIE)
		printf("%ldms %d died\n", ms, index);
	else if (state == S_FORK)
		printf("%ldms %d has taken second fork\n", ms, index);
	else if (state == F_FORK)
		printf("%ldms %d has taken first fork\n", ms, index);
	else
		error("wrong enum for the state message\n");
}

int	routine(t_monitor *m, t_philo *p)
{
	int	i;

	i = 0;
	p->last_meal_time = m->beginning;
	while (m->end_flag == true)
	{
		philo_eat(m, p);
	// sleep
		state_message(m->beginning, SLEEP, p->index);
		philo_sleep(m, m->sleep);
	// think


	// death_checker
		death_checker(m, p, p->last_meal_time);
	//		again!
	// if time_to_die passed --> die flag --> monitor ends the simulation}
	}
	return (1);
}
