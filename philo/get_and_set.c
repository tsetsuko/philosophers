/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:31:50 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/08/13 19:01:02 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// locks and unlocks specific variables in the critical zone so only
// one thread can read from it
long	get_long(long *var, pthread_mutex_t *lock)
{
	long ret;

	pthread_mutex_lock(lock);
	ret = *var;
	pthread_mutex_unlock(lock);
	return (ret);
}

void	set_long(long *src, long dest, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*src = dest;
	pthread_mutex_unlock(lock);
}

bool	get_bool(bool *var, pthread_mutex_t *lock)
{
	bool ret;

	pthread_mutex_lock(lock);
	ret = *var;
	pthread_mutex_unlock(lock);
	return (ret);
}

void	set_bool(bool *src, bool dest, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*src = dest;
	pthread_mutex_unlock(lock);
}