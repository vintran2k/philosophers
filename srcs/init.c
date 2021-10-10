/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 17:18:42 by vintran           #+#    #+#             */
/*   Updated: 2021/10/08 14:01:50 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_error(int ac, char **av)
{
	int		i;
	int		j;
	long	n;

	i = 0;
	while (++i < ac)
	{
		n = long_atoi(av[i]);
		if (n > 2147483647 || n == 0)
			return (-1);
		j = -1;
		while (av[i][++j])
		{
			if (!ft_isdigit(av[i][j]))
				return (-1);
		}
	}
	return (0);
}

int	init_info(int ac, char **av, t_info *info)
{
	if (check_error(ac, av) == -1)
		return (-1);
	info->n_philo = (int)long_atoi(av[1]);
	info->t_to_die = (unsigned int)long_atoi(av[2]);
	info->t_to_eat = (unsigned int)long_atoi(av[3]);
	info->t_to_sleep = (unsigned int)long_atoi(av[4]);
	if (ac == 6)
		info->n_meals = (int)long_atoi(av[5]);
	else
		info->n_meals = -1;
	info->stop = 0;
	pthread_mutex_init(&info->m_info, NULL);
	pthread_mutex_init(&info->m_stop, NULL);
	pthread_mutex_init(&info->m_msg, NULL);
	pthread_mutex_init(&info->m_last_eat, NULL);
	return (0);
}

void	init_philos(t_p *philos, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->n_philo)
	{
		philos[i].info = info;
		philos[i].id = i + 1;
		philos[i].n = info->n_philo;
		philos[i].count = 0;
		philos[i].stop = 0;
		philos[i].t_die = info->t_to_die;
		philos[i].t_eat = info->t_to_eat;
		philos[i].t_sleep = info->t_to_sleep;
		philos[i].n_meals = info->n_meals;
		i++;
	}
}

void	distribute_forks(t_p *p, pthread_mutex_t *forks, int n)
{
	int	i;

	pthread_mutex_init(&forks[0], NULL);
	p[0].l_fork = &forks[0];
	p[0].r_fork = NULL;
	p[0].r_fork = &forks[n - 1];
	i = 1;
	while (i < n)
	{
		pthread_mutex_init(&forks[i], NULL);
		p[i].l_fork = &forks[i];
		p[i].r_fork = &forks[i - 1];
		i++;
	}
}
