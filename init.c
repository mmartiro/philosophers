/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:28:17 by mmartiro          #+#    #+#             */
/*   Updated: 2022/03/16 18:28:19 by mmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_t(t_base *base)
{
	int	i;
	int	r;

	i = 0;
	r = 1;
	while (i < base->p_count)
	{
		if (pthread_create(&base->p_array[i].p_th, NULL, &routine,
				(void *)&base->p_array[i]) != 0)
			r = esc("Error: Failed to create thread");
		i++;
		usleep(50);
	}
	i = 0;
	while (i < base->p_count)
	{
		if (pthread_join(base->p_array[i].p_th, NULL) != 0)
			r = esc("Error: Failed to create thread");
		i++;
	}
	return (r);
}

int	init_forks(t_base *base)
{
	int	i;
	int	r;

	i = 0;
	r = 1;
	base->state = 0;
	while (i < base->p_count)
	{
		base->p_array[i].last_eat = gettime();
		base->p_array[i].p_n = i + 1;
		base->p_array[i].m_eat = 0;
		base->p_array[i].lfork = i;
		base->p_array[i].rfork = (i + base->p_count - 1) % base->p_count;
		base->p_array[i].base = base;
		if (pthread_mutex_init(&base->p_mutex[i], NULL) != 0)
			r = esc("mutex init failed\n");
		base->p_array[i].start = gettime();
		i++;
	}
	if (pthread_mutex_init(&base->write_mutex, NULL) != 0)
		r = esc("mutex init failed\n");
	if (pthread_mutex_init(&base->p_state, NULL) != 0)
		r = esc("mutex init failed\n");
	return (r);
}

int	init(t_base *base)
{
	base->p_array = (t_philo *)malloc(sizeof(t_philo) * base->p_count);
	if (!base->p_array)
		esc("Malloc Error\n");
	base->p_mutex = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * base->p_count);
	if (!base->p_mutex)
		esc("Malloc Error\n");
	return (init_forks(base) && create_t(base));
}

int	free_init(t_base *base)
{
	int	i;
	int	r;

	i = 0;
	r = 1;
	while (i < base->p_count)
	{
		if (pthread_mutex_destroy(&base->p_mutex[i]) != 0)
			r = esc("mutex destroy failed\n");
		i++;
	}
	pthread_mutex_destroy(&base->write_mutex);
	pthread_mutex_destroy(&base->p_state);
	free(base->p_mutex);
	free(base->p_array);
	return (r);
}
