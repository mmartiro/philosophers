/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:27:42 by mmartiro          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:44 by mmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_mess(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->base->write_mutex);
	if (!philo->base->state)
		printf("%ldms	Philo:%d %s\n", gettime() - philo->start, philo->p_n, s);
	pthread_mutex_unlock(&philo->base->write_mutex);
}

int	parsing(char **argv, t_base *base)
{
	base->p_count = ft_atoi(argv[1]);
	base->p_die = ft_atoi(argv[2]);
	base->p_eat = ft_atoi(argv[3]);
	base->p_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		base->p_musteat = ft_atoi(argv[5]);
		if (base->p_musteat <= 0)
			return (0);
	}
	if (base->p_count <= 0 || base->p_count > 200
		|| base->p_die < 60 || base->p_eat < 60
		|| base->p_sleep < 60)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_base	base;

	if (argc != 5 && argc != 6)
		return (esc("Arguments count is't correct\n"));
	if (!parsing(argv, &base))
		return (esc("Error: invalid argument\n"));
	if (!init(&base))
		return (0);
	if (!free_init(&base))
		return (0);
	return (0);
}
