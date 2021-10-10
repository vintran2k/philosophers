/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 16:00:41 by vintran           #+#    #+#             */
/*   Updated: 2021/10/08 14:01:37 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_info
{
	int				n_philo;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	unsigned int	t_start;
	int				n_meals;
	int				*meals;
	int				stop;
	pthread_mutex_t	m_info;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_msg;
	pthread_mutex_t	m_last_eat;
	
}				t_info;

typedef struct s_p
{
	t_info			*info;
	int				id;
	int				n;
	int				count;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				n_meals;
	unsigned int	t_last_eat;
	int				stop;
	pthread_t		faucheuse;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}				t_p;

void			ft_bzero(void *s, size_t n);
int				ft_isdigit(int c);
long			long_atoi(char *str);
unsigned int	get_time(void);
void			print_status(t_p *p, char *status); //
void			print_msg(t_p *p, char *msg);
int				init_info(int ac, char **av, t_info *info);
void			init_philos(t_p *philos, t_info *info);
void			distribute_forks(t_p *p, pthread_mutex_t *forks, int n);
void			ft_usleep(unsigned int time_in_ms);
int				launching_threading(t_p *philos, t_info *info, pthread_t *th);
void			activity(t_p *p);
void			destroy_mutex(t_info *info, pthread_mutex_t *forks);

#endif
