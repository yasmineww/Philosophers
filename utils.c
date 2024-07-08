/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:17:03 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/08 14:36:39 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_error(char *str)
{
	printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
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
	while (*str >= '0' && *str <= '9')
	{
		res = (res * 10) + (*str - '0');
		str++;
	}
	if (res >= 2147483648 || res <= -2147483649)
		print_error("Argument out of range");
	return (res);
}
