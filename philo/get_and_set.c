/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_and_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:31:50 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/09/12 13:12:23 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// locks and unlocks specific variables in the critical zone so only
// one thread can read from it
long	get_long(long *var, pthread_mutex_t *lock)
{
	long ret;

	safe_mutex_functions(LOCK, lock);
	ret = *var;
	safe_mutex_functions(UNLOCK, lock);
	return (ret);
}

void	set_long(long *src, long dest, pthread_mutex_t *lock)
{
	safe_mutex_functions(LOCK, lock);
	*src = dest;
	safe_mutex_functions(UNLOCK, lock);
}

bool	get_bool(bool *var, pthread_mutex_t *lock)
{
	bool ret;

	safe_mutex_functions(LOCK, lock);
	ret = *var;
	safe_mutex_functions(UNLOCK, lock);
	return (ret);
}

void	set_bool(bool *src, bool dest, pthread_mutex_t *lock)
{
	safe_mutex_functions(LOCK, lock);
	*src = dest;
	safe_mutex_functions(UNLOCK, lock);
}