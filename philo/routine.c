/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 23:10:21 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/11 15:20:53 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// this function will provide sleep for the philo but it will also check
// if the simulation hasn't stopped in the meanwhile
void	philo_sleep(t_monitor *m, long time)
{
	// long	wake_up;
	long	now;
	(void)m;

	now = get_ms();
	// wake_up = now + time;
	while (time > get_ms() - now)
	{
		// if (get_bool(&m->end_flag, &m->end_lock))
		// 	break ;
		usleep(100);
	}
}

int	death_checker_s(t_monitor *m, t_philo *philo, long beginning)
{
	long	now_time;

	timestamp(beginning, &now_time);
	if (m->die <= now_time)
	{
		// philo->death_flag = true;
		state_message(DIE, philo);
		m->end_flag = true;
		//end simulation
	}
	return (1);
}

void	single_philo_routine(t_monitor *m, t_philo *p)
{
	safe_mutex_functions(LOCK, p->first_fork);
	state_message(F_FORK, p);
	philo_sleep(m, m->die); 
	death_checker_s(m, p, m->beginning);
	safe_mutex_functions(UNLOCK, p->first_fork);
}

void	state_message(t_state state, t_philo *p)
{
	long	ms;
	long	beginning;

	// create a write lock
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
	t_philo 	*p;
	// pthread_t	death_checker;

	i = 0;
	// printf("entered routine\n");
	p = (t_philo *)data;
	// safe_mutex_functions(LOCK, p->last_meal_lock);
	// p->last_meal_time = get_long(&p->monitor->beginning, &p->monitor->lock_long_var);
	// pthread_mutex_unlock(&p->last_meal_lock);
	// printf("beginning [%d]: %ld\n", p->index, p->monitor->beginning);
	// printf("hey it's %d\n", p->index);
	// if (pthread_create(&death_checker, NULL, &death_checker_thread, p) == 0)
	// 	printf("supervisor goes\n");
	// while (get_bool(&p->monitor->end_flag, &p->monitor->lock_bools) == false)
	while (1)
	{
		// printf("entered routine loop\n");
		philo_eat(p->monitor, p);
	// sleep
		state_message(SLEEP, p);
		// printf("%ld\n", get_long(&p->monitor->sleep, &p->monitor->lock_long_var));
		// usleep(2000000);
		philo_sleep(p->monitor, get_long(&p->monitor->sleep, &p->monitor->lock_long_var));
	// think
		state_message(THINK, p);
		// if (get_bool(p->end_flag, p->end_lock) == true)
		// 	printf("why end\n");
	// death_checker
	//		again!
	// if time_to_die passed --> die flag --> monitor ends the simulation}
	}
	return (NULL);
	
}
