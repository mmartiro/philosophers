/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:49:51 by mmartiro          #+#    #+#             */
/*   Updated: 2022/03/18 19:49:54 by mmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	gettime(void)
{
	struct timeval		time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_usleep(unsigned long long time)
{
	struct timeval		t;
	unsigned long long	now;

	gettimeofday(&t, NULL);
	now = t.tv_sec * 1000 + t.tv_usec / 1000;
	while (gettime() - now < time)
		usleep(100);
}
