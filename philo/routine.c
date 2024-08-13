/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:21 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/13 19:30:43 by zogorzeb         ###   ########.fr       */
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
		state_message(DIE, philo);
		m->end_flag = true;
		//end simulation
	}
	return (1);
}

void	single_philo_routine(t_monitor *m, t_philo *p)
{
	pthread_mutex_lock(&p->forks[p->position]);
	state_message(F_FORK, p);
	philo_sleep(m, m->die);
	death_checker(m, p, m->beginning);
	pthread_mutex_unlock(&p->forks[p->position]);
}

void	state_message(t_state state, t_philo *p)
{
	long	ms;
	long	beginning;

	// create a write lock
	pthread_mutex_lock(&p->monitor->write_message);

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
	else
		error("wrong enum for the state message\n");
	pthread_mutex_unlock(&p->monitor->write_message);

}

void	*routine(void *data)
{
	int			i;
	t_philo 	*p;
	// pthread_t	death_checker;

	i = 0;
	p = (t_philo *)data;
	// pthread_mutex_lock(&p->last_meal_lock);
	p->last_meal_time = get_long(&p->monitor->beginning, &p->monitor->lock_long_var);
	// pthread_mutex_unlock(&p->last_meal_lock);
	// printf("beginning [%d]: %ld\n", p->index, p->monitor->beginning);
	// printf("hey it's %d\n", p->index);
	// if (pthread_create(&death_checker, NULL, &death_checker_thread, p) == 0)
	// 	printf("supervisor goes\n");
	// while (get_bool(&p->monitor->end_flag, &p->monitor->lock_bools) == false)
	while (1)
	{
		printf("entered routine loop\n");
		philo_eat(p->monitor, p);
	// sleep
		state_message(SLEEP, p);
		philo_sleep(p->monitor, p->monitor->sleep);
	// think
		state_message(THINK, p);
	// death_checker
	//		again!
	// if time_to_die passed --> die flag --> monitor ends the simulation}
	}
	return (NULL);
	
}
