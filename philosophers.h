/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmartiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:27:53 by mmartiro          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:55 by mmartiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <pthread.h>

typedef struct s_philo
{
	int				p_n;
	int				rfork;
	int				lfork;
	int				m_eat;
	long			last_eat;	
	long			start;		
	pthread_t		p_th;
	struct s_base	*base;
}			t_philo;

typedef struct s_base
{
	int				p_count;
	long			p_die;
	long			p_eat;
	long			p_sleep;
	int				p_musteat;
	int				state;
	t_philo			*p_array;
	pthread_mutex_t	*p_mutex;
	pthread_mutex_t	p_state;
	pthread_mutex_t	must_eat;
	pthread_mutex_t	write_mutex;
}				t_base;

int		ft_atoi(const char *str);
int		parsing(char **argv, t_base *base);
int		init(t_base *base);
int		esc(char *s);
int		free_init(t_base *base);
void	*routine(void *arg);
int		create_t(t_base *base);
long	gettime(void);
void	*die_philo(void *ph);
void	ft_usleep(unsigned long long time);
void	print_mess(char *s, t_philo *philo);

#endif
