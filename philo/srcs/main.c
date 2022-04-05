/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:18:02 by vintran           #+#    #+#             */
/*   Updated: 2022/04/05 14:02:46 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_ptrs(t_p *philos, pthread_t *th, pthread_mutex_t *forks)
{
	if (philos)
	{
		free(philos);
		philos = NULL;
	}
	if (th)
	{
		free(th);
		th = NULL;
	}
	if (forks)
	{
		free(forks);
		forks = NULL;
	}
}

int	malloc_error(t_p *philos, pthread_t *th, pthread_mutex_t *forks)
{
	free_ptrs(philos, th, forks);
	perror("philo");
	return (-1);
}

int	malloc_ptrs(t_p **philos, pthread_t **th, pthread_mutex_t **forks, int n)
{
	*philos = malloc(sizeof(t_p) * n);
	if (!*philos)
		return (malloc_error(*philos, *th, *forks));
	*th = malloc(sizeof(pthread_t) * n);
	if (!*th)
		return (malloc_error(*philos, *th, *forks));
	*forks = malloc(sizeof(pthread_mutex_t) * n);
	if (!*forks)
		return (malloc_error(*philos, *th, *forks));
	return (0);
}

int	main(int ac, char **av)
{
	t_info			info;
	t_p				*philos;
	pthread_t		*th;
	pthread_mutex_t	*forks;

	if (ac < 5 || ac > 6 || init_info(ac, av, &info) == -1)
	{
		printf("Error\nInvalid arguments\n");
		return (1);
	}
	philos = NULL;
	th = NULL;
	forks = NULL;
	if (malloc_ptrs(&philos, &th, &forks, info.n_philo) == -1)
		return (1);
	init_philos(philos, &info);
	distribute_forks(philos, forks, info.n_philo);
	launching_threading(philos, &info, th);
	destroy_mutex(&info, forks);
	free_ptrs(philos, th, forks);
	return (0);
}
