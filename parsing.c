/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/12 10:30:30 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_valid(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] >= '0' && av[i] <= '9') || av[i] == '+'
			|| av[i] == ' ')
			i++;
		else
			ft_putstr_fd("Invalid argument syntax", 2);
	}
}

void	check_empty(char *av)
{
	int	i;

	i = 0;
	if (!av[0])
		ft_putstr_fd("Empty argument", 2);
	while ((av[i] >= 9 && av[i] <= 13) || av[i] == ' ')
		i++;
	if (!av[i])
		ft_putstr_fd("Empty argument", 2);
}

void	parsing(char **av, t_philo **philo)
{
	int	i;

	i = 1;
	while (av[i])
	{
		check_empty(av[i]);
		check_valid(av[i]);
		i++;
	}
	(*philo) = malloc(sizeof(t_philo));
	(*philo)->number_of_philos = my_atoi(av[1]);
	(*philo)->time_to_die = my_atoi(av[2]);
	(*philo)->time_to_eat = my_atoi(av[3]);
	(*philo)->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		(*philo)->nmbr_times_to_eat = my_atoi(av[5]);
}
