/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 18:18:02 by vintran           #+#    #+#             */
/*   Updated: 2021/11/14 16:27:15 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_vars(t_p *philos, pthread_t *th, pthread_mutex_t *forks)
{
	free(philos);
	free(th);
	free(forks);
}

int	malloc_error(void)
{
	perror("philo");
	return (1);
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
	philos = malloc(sizeof(t_p) * info.n_philo);
	if (!philos)
		return (malloc_error());
	th = malloc(sizeof(pthread_t) * info.n_philo);
	if (!th)
		return (malloc_error());
	forks = malloc(sizeof(pthread_mutex_t) * info.n_philo);
	if (!forks)
		return (malloc_error());
	init_philos(philos, &info);
	distribute_forks(philos, forks, info.n_philo);
	launching_threading(philos, &info, th);
	destroy_mutex(&info, forks);
	free_vars(philos, th, forks);
	return (0);
}
