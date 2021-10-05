/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:42:30 by vintran           #+#    #+#             */
/*   Updated: 2021/09/23 17:58:08 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
void	print_msg(t_p *p, char *msg)
{
	pthread_mutex_lock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_stop);
	if (!p->info->stop)
		printf("%7dms  %3d    %s\n", get_time() - p->info->t_start, p->id, msg);
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_unlock(&p->info->m_stop);
}
*/

int		len(long nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		len++;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_status(t_p *p, char *status)
{
	char	*time;
	char	*id;
	char	*res;
	int		reslen;
	
	pthread_mutex_lock(&p->info->m_msg);
	pthread_mutex_lock(&p->info->m_stop);
	if (p->info->stop == 1)
	{
		pthread_mutex_unlock(&p->info->m_msg);
		pthread_mutex_unlock(&p->info->m_stop);
		return ;
	}
	time = ft_itoa((int)(get_time() - p->info->t_start));
	id = ft_itoa(p->id);
	reslen = ft_strlen(time) + ft_strlen(id) + ft_strlen(status) + 4;
	res = malloc(reslen);
	res[0] = '\0';
	ft_strcat(res, time);
	ft_strcat(res, " ");
	ft_strcat(res, id);
	ft_strcat(res, " ");
	ft_strcat(res, status);
	ft_strcat(res, "\n");
	write(1, res, reslen);
	pthread_mutex_unlock(&p->info->m_msg);
	pthread_mutex_unlock(&p->info->m_stop);
	free(time);
	free(id);
	free(res);
}
