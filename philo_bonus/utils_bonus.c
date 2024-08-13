/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:17:03 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/13 16:09:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_empty(char *av)
{
	int	i;

	i = 0;
	if (!av[0])
	{
		ft_putstr_fd("Empty argument!", 2);
		return (1);
	}
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == ' ')
		i++;
	if (!av[i])
	{
		ft_putstr_fd("Empty argument!", 2);
		return (1);
	}
	return (0);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char	*av)
{
	int	count;

	count = 0;
	while (*av)
	{
		count++;
		av++;
	}
	return (count);
}

int	my_atoi(char *str)
{
	long	res;

	res = 0;
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	return (res);
}
