/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vintran <vintran@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 16:42:30 by vintran           #+#    #+#             */
/*   Updated: 2021/10/13 14:02:13 by vintran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	itoa_len(long nb)
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
	char	*str;
	long	n;
	int		i;

	n = nb;
	i = itoa_len(n);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
		str[0] = 48;
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

int	create_string(t_p *p, char *status, char **str)
{
	char	*strs[3];
	int		reslen;
	int		i;

	strs[0] = ft_itoa((int)(get_time() - p->info->t_start));
	strs[1] = ft_itoa(p->id);
	strs[2] = status;
	reslen = ft_strlen(strs[0]) + ft_strlen(strs[1]) + ft_strlen(strs[2]) + 4;
	*str = malloc(reslen);
	*str[0] = '\0';
	i = 0;
	while (i < 3)
	{
		ft_strcat(*str, strs[i]);
		if (i < 2)
		{
			ft_strcat(*str, " ");
			free(strs[i]);
		}
		i++;
	}
	ft_strcat(*str, "\n");
	return (reslen);
}

void	print_status(t_p *p, char *status)
{
	char	*str;
	int		len;

	pthread_mutex_lock(&p->info->m_stop);
	if (p->info->stop == 1)
	{
		pthread_mutex_unlock(&p->info->m_stop);
		return ;
	}
	if (!ft_strcmp(status, "died"))
		p->info->stop = 1;
	pthread_mutex_unlock(&p->info->m_stop);
	len = create_string(p, status, &str);
	write(1, str, len);
	free(str);
}
