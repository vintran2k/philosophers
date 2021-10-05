/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:49:48 by vintran           #+#    #+#             */
/*   Updated: 2021/10/05 16:58:57 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_n_meals(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->n)
	{
		pthread_mutex_lock(&p->info->m_meals);
		if (p->info->meals[i] < p->n_meals)
		{
			pthread_mutex_unlock(&p->info->m_meals);
			return (0);
		}
		pthread_mutex_unlock(&p->info->m_meals);
		i++;
	}
	pthread_mutex_lock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_stop);
	if (!p->info->stop)
		printf("Each philosopher ate %d time(s)\n", p->n_meals);
	p->info->stop = 1;
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_unlock(&p->info->m_stop);
	return (1);
}

void	*is_dead(void *arg)
{
	t_p	*p;
	int	stop;

	p = (t_p *)arg;
	stop = 0;
	while (!stop)
	{
		if (p->id == 1 && p->n_meals != -1)
			check_n_meals(p);
		pthread_mutex_lock(&p->info->m_last_eat);
		if (get_time() - p->t_last_eat >= p->t_die)
		{
			pthread_mutex_unlock(&p->info->m_last_eat);
			print_status(p, "died");
			pthread_mutex_lock(&p->info->m_stop);
			p->info->stop = 1;
			pthread_mutex_unlock(&p->info->m_stop);
		}
		else
			pthread_mutex_unlock(&p->info->m_last_eat);
		pthread_mutex_lock(&p->info->m_stop);
		stop = p->info->stop;
		pthread_mutex_unlock(&p->info->m_stop);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_p	*p;
	int	stop;

	p = (t_p *)arg;
	p->t_last_eat = p->info->t_start;
	if (pthread_create(&p->faucheuse, NULL, &is_dead, p))
		perror("pthread_create failled");
	pthread_detach(p->faucheuse);
	if (p->id % 2 == 0)
		ft_usleep(p->t_eat / 10);
	stop = 0;
	while (!stop)
	{
		activity(p);
		pthread_mutex_lock(&p->info->m_stop);
		stop = p->info->stop;
		pthread_mutex_unlock(&p->info->m_stop);
	}
	return (NULL);
}

void	destroy_mutex(t_info *info, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(&info->m_last_eat);
	pthread_mutex_destroy(&info->m_meals);
	pthread_mutex_destroy(&info->m_msg);
	pthread_mutex_destroy(&info->m_stop);
}

int	launching_threading(t_p *philos, t_info *info, pthread_t *th)
{
	int	i;

	i = 0;
	info->t_start = get_time();
	while (i < info->n_philo)
	{
		if (pthread_create(&th[i], NULL, &routine, &philos[i]))
			perror("pthread_create failled");
		usleep(30);
		i++;
	}
	i = 0;
	while (i < info->n_philo)
	{
		if (pthread_join(th[i], NULL))
			perror("join failled");
		i++;
	}
	return (0);
}


/*
0ms    1    has taken a fork
      0ms    1    has taken a fork
      0ms    1    is eating
      1ms    3    has taken a fork
      1ms    3    has taken a fork
      1ms    3    is eating
    200ms    1    is sleeping
    200ms    4    has taken a fork
    201ms    4    has taken a fork
    201ms    4    is eating
    201ms    2    has taken a fork
    201ms    2    has taken a fork */