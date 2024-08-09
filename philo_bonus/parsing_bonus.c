/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/09 10:49:37 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_data(t_info **info)
{
	int	i;

	i = -1;
	sem_unlink("/forks");
	sem_unlink("/print");
	(*info)->forks = sem_open("/forks", O_CREAT, 0644, (*info)->number_of_philosophers);
	if ((*info)->forks == SEM_FAILED)
		return (1);
	(*info)->print = sem_open("/print", O_CREAT, 0644, 1);
	if ((*info)->print == SEM_FAILED)
		return (1);
	return (0);
}

int	save_data(char **av, t_info **info)
{
	(*info)->full = 0;
	(*info)->meal = 0;
	(*info)->time = get_time();
	(*info)->number_of_philosophers = my_atoi(av[1]);
	(*info)->time_to_die = my_atoi(av[2]);
	(*info)->time_to_eat = my_atoi(av[3]);
	(*info)->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		(*info)->must_eat = my_atoi(av[5]);
	else
		(*info)->must_eat = -1;
	if ((*info)->number_of_philosophers == 0 || (*info)->must_eat == 0)
		return (1);
	return (0);
}

int	parsing(char **av, t_info **info)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_empty(av[i]) || check_valid(av[i]))
			exit(1);
		i++;
	}
	(*info) = malloc(sizeof(t_info));
	if (!*info)
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	if (save_data(av, info))
	{
		free_leaks(*info);
		exit(0);
	}
	init_data(info);
	return (0);
}
