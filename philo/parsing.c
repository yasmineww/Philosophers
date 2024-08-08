/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 16:35:20 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			return (ft_putstr_fd("Invalid argument syntax!", 2), 1);
	}
	return (0);
}

int	init_philo(t_info **info)
{
	int	i;

	i = -1;
	(*info)->philo = malloc (sizeof(t_philo) * (*info)->number_of_philosophers);
	if (!(*info)->philo)
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	(*info)->forks = malloc (sizeof(pthread_mutex_t)
			*(*info)->number_of_philosophers);
	if (!(*info)->forks)
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	while (++i < (*info)->number_of_philosophers)
	{
		if (pthread_mutex_init(&(*info)->forks[i], NULL))
			return (ft_putstr_fd("Mutex init failed!", 2), 1);
		(*info)->philo[i].id = i + 1;
		(*info)->philo[i].meal = 0;
		(*info)->philo[i].r_fork = &(*info)->forks[i];
		(*info)->philo[i].l_fork = &(*info)->forks[(i + 1)
			% (*info)->number_of_philosophers];
		(*info)->philo[i].info = *info;
	}
	return (0);
}

int	save_data(char **av, t_info **info)
{
	(*info)->full = 0;
	(*info)->time = get_time();
	if (pthread_mutex_init(&(*info)->print, NULL))
		return (ft_putstr_fd("Mutex init failed!", 2), 1);
	if (pthread_mutex_init(&(*info)->lock_death, NULL))
		return (ft_putstr_fd("Mutex init failed!", 2), 1);
	if (pthread_mutex_init(&(*info)->lock_full, NULL))
		return (ft_putstr_fd("Mutex init failed!", 2), 1);
	(*info)->number_of_philosophers = my_atoi(av[1]);
	(*info)->time_to_die = my_atoi(av[2]);
	(*info)->time_to_eat = my_atoi(av[3]);
	(*info)->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		(*info)->must_eat = my_atoi(av[5]);
	else
		(*info)->must_eat = -1;
	return (0);
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
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	if (save_data(av, info) || init_philo(info))
		return (free_leaks(*info), 1);
	return (0);
}
