/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 16:32:34 by vintran           #+#    #+#             */
/*   Updated: 2021/10/12 18:14:19 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_p *p, char *msg)
{
	pthread_mutex_lock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_stop);
	if (!p->info->stop)
		printf("%7dms  %3d    %s\n", get_time() - p->info->t_start, p->id, msg);
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_unlock(&p->info->m_stop);
}

void	droitier(t_p *p)
{
	pthread_mutex_lock(p->r_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->r_fork);
		ft_usleep(p->t_die);
		return ;
	}
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "is eating");
	pthread_mutex_unlock(&p->info->m_msg);
	p->count++;
	pthread_mutex_lock(&p->info->m_last_eat);
	p->t_last_eat = get_time();
	pthread_mutex_unlock(&p->info->m_last_eat);
	ft_usleep(p->t_eat);
	pthread_mutex_unlock(p->r_fork);
	pthread_mutex_unlock(p->l_fork);
}

void	gaucher(t_p *p)
{
	pthread_mutex_lock(p->l_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n == 1)
	{
		pthread_mutex_unlock(p->l_fork);
		ft_usleep(p->t_die);
		return ;
	}
	pthread_mutex_lock(p->r_fork);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "has taken a fork");
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "is eating");
	pthread_mutex_unlock(&p->info->m_msg);
	p->count++;
	pthread_mutex_lock(&p->info->m_last_eat);
	p->t_last_eat = get_time();
	pthread_mutex_unlock(&p->info->m_last_eat);
	ft_usleep(p->t_eat);
	pthread_mutex_unlock(p->l_fork);
	pthread_mutex_unlock(p->r_fork);
}

void	eat_activity(t_p *p)
{
	if (p->n % 2 != 0 && (p->id == 1 || p->id == p->n))
		pthread_mutex_lock(&p->info->m_impair);	//
	//if (p->n % 2 == 0)
	//{
		if (p->id % 2 == 0)
			droitier(p);
		else
			gaucher(p);
	//}
	//else
	//{
		//droitier(p);
	//}
	if (p->n % 2 != 0  && (p->id == 1 || p->id == p->n))
		pthread_mutex_unlock(&p->info->m_impair);	//
}

void	activity(t_p *p)
{
	eat_activity(p);
	if (p->n_meals != -1 && p->count == p->n_meals)
	{
		pthread_mutex_lock(&p->info->m_stop);
		p->stop = 1;
		pthread_mutex_unlock(&p->info->m_stop);
		return ;
	}
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "is sleeping");
	pthread_mutex_unlock(&p->info->m_msg);
	ft_usleep(p->t_sleep);
	pthread_mutex_lock(&p->info->m_msg);
	print_status(p, "is thinking");
	pthread_mutex_unlock(&p->info->m_msg);
	if (p->n % 2 != 0)
		ft_usleep(100);
}
