/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 13:59:09 by vintran           #+#    #+#             */
/*   Updated: 2021/10/13 14:00:01 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time(void)
{
	unsigned int	ret;
	struct timeval	time;

	ret = 0;
	if (gettimeofday(&time, NULL) == -1)
	{
		perror("gettimeofday() failled");
		return (0);
	}
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	ft_usleep(unsigned int time_in_ms)
{
	unsigned int	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}
