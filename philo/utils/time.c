/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zogorzeb <zogorzeb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:26:46 by zogorzeb          #+#    #+#             */
/*   Updated: 2024/10/03 14:27:12 by zogorzeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	timestamp(long beginning, long *timestamp)
{
	long	ms;

	ms = get_ms();
	*timestamp = ms - beginning;
}

long	get_ms(void)
{
	struct timeval	tv1;

	gettimeofday(&tv1, NULL);
	return ((tv1.tv_sec * 1000) + tv1.tv_usec / 1000);
}
