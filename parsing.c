/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/28 18:09:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_data_limit(t_info *info)
{
	if (info->total_philos == 0)
	{
		ft_putstr_fd("There are no philosophers on the table!", 2);
		return (1);
	}
	else if (info->total_philos > 200)
	{
		ft_putstr_fd("Number of philoshophers should't exceed 200!", 2);
		return (1);
	}
	else if (info->time_to_die < 60 || info->time_to_eat < 60
		|| info->time_to_sleep < 60)
	{
		ft_putstr_fd("Time should be at least 60ms!", 2);
		return (1);
	}
	return (0);
}

int	check_valid(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] >= '0' && av[i] <= '9') || av[i] == '+'
			|| av[i] == ' ')
			i++;
		else
		{
			ft_putstr_fd("Invalid argument syntax!", 2);
			return (1);
		}
	}
	
	return (0);
}

int	init_philo(t_info **info)
{
	int	i;

	i = -1;
	(*info)->philo = malloc (sizeof(t_philo) * (*info)->total_philos);
	(*info)->forks = malloc (sizeof(pthread_mutex_t) * (*info)->total_philos);
	if (!(*info)->philo || !(*info)->forks)
	{
		ft_putstr_fd("Malloc failed!", 2);
		return (1);
	}
	while (++i < (*info)->total_philos)
	{
		if (pthread_mutex_init(&(*info)->forks[i], NULL))
		{
			ft_putstr_fd("Mutex init failed!", 2);
			return (1);
		}
		(*info)->philo[i].id = i + 1;
		(*info)->philo[i].meal = 0;
		(*info)->philo[i].r_fork = &(*info)->forks[i];
		(*info)->philo[i].l_fork = &(*info)->forks[(i + 1)
			% (*info)->total_philos];
		(*info)->philo[i].info = *info;
	}
	return (0);
}

void	save_data(char **av, t_info **info)
{
	(*info)->death = 0;
	(*info)->time = 0;
	(*info)->total_philos = my_atoi(av[1]);
	(*info)->time_to_die = my_atoi(av[2]);
	(*info)->time_to_eat = my_atoi(av[3]);
	(*info)->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		(*info)->must_eat = my_atoi(av[5]);
	else
		(*info)->must_eat = -1;
}

int	parsing(char **av, t_info **info)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_empty(av[i]) || check_valid(av[i]))
			return (1);
		i++;
	}
	(*info) = malloc(sizeof(t_info));
	if (!*info)
	{
		ft_putstr_fd("Malloc failed!", 2);
		return (1);
	}
	save_data(av, info);
	if (check_data_limit(*info))
		return (free_leaks(*info) ,1);	
	init_philo(info);
	return (0);
}
