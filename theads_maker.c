/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   theads_maker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:28:17 by mmartiro          #+#    #+#             */
/*   Updated: 2022/03/16 18:28:19 by mmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_eating(t_philo *philo)
{
	if (philo->base->p_count != 1)
		pthread_mutex_lock(&philo->base->p_mutex[philo->rfork]);
	pthread_mutex_lock(&philo->base->p_mutex[philo->lfork]);
	print_mess("has taken a fork", philo);
	philo->last_eat = gettime();
	print_mess("is eating", philo);
	ft_usleep(philo->base->p_eat);
	pthread_mutex_lock(&philo->base->must_eat);
	philo->m_eat++;
	pthread_mutex_unlock(&philo->base->must_eat);
	if (philo->base->p_count != 1)
		pthread_mutex_unlock(&philo->base->p_mutex[philo->rfork]);
	pthread_mutex_unlock(&philo->base->p_mutex[philo->lfork]);
	return (0);
}

void	help(t_philo *philo)
{
	ft_usleep(philo->base->p_eat);
	pthread_mutex_lock(&philo->base->write_mutex);
	if (!philo->base->state)
		printf("%ldms Philo:%d is dead\n", philo->base->p_eat, philo->p_n);
	pthread_mutex_unlock(&philo->base->write_mutex);
	pthread_mutex_lock(&philo->base->p_state);
	philo->base->state = 1;
	pthread_mutex_unlock(&philo->base->p_state);
}

void	*die_philo(void *ph)
{
	t_philo	*philo;

	philo = ph;
	while (!philo->base->state)
	{
		if (gettime() - philo->last_eat > philo->base->p_die)
		{
			print_mess("is dead", philo);
			pthread_mutex_lock(&philo->base->p_state);
			philo->base->state = 1;
			pthread_mutex_unlock(&philo->base->p_state);
			break ;
		}
	}
	return (NULL);
}

void	*must_eat(void *ph)
{
	t_philo	*philo;
	int		i;
	int		p_c;

	philo = ph;
	p_c = 0;
	i = 0;
	while (i < philo->base->p_count)
	{
		if (philo->base->p_array[i].m_eat >= philo->base->p_musteat)
			p_c++;
		i++;
	}
	if (p_c == philo->base->p_count && philo->base->state == 0)
	{
		pthread_mutex_lock(&philo->base->p_state);
		philo->base->state = 1;
		pthread_mutex_unlock(&philo->base->p_state);
		pthread_mutex_lock(&philo->base->write_mutex);
		printf("All the philosophers are alive!!!\n");
		pthread_mutex_unlock(&philo->base->write_mutex);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	pthread_t	die;
	pthread_t	m_eat;

	philo = arg;
	if (pthread_create(&die, NULL, die_philo, (void *)philo))
		esc("Error: Failed to create thread");
	pthread_detach(die);
	while (!philo->base->state)
	{
		if (philo->base->p_count == 1)
			help(philo);
		is_eating(philo);
		if (philo->base->p_musteat > 0)
		{
			if (pthread_create(&m_eat, NULL, must_eat, (void *)philo))
				esc("Error: Failed to create thread");
			pthread_detach(m_eat);
		}
		print_mess("is sleeping", philo);
		ft_usleep(philo->base->p_sleep);
		print_mess("is thinking", philo);
	}
	return ((void *)philo);
}
