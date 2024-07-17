/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 11:17:03 by ymakhlou         ###   ########.fr       */
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

void	init_philo(t_info **info)
{
	int	i;

	i = (*info)->number_of_philos;
	(*info)->philo = malloc (sizeof(t_philo) * i);
	(*info)->forks = malloc (sizeof(pthread_mutex_t) * i);
	if (!(*info)->philo || !(*info)->forks)
		ft_putstr_fd("Malloc failed", 2);
	while (i > 0)
	{
		i--;
		if (pthread_mutex_init(&(*info)->forks[i], NULL))
			ft_putstr_fd("Mutex init failed", 2);
		(*info)->philo[i].id = i + 1;
		(*info)->philo[i].meal = 0;
		(*info)->philo[i].r_fork = &(*info)->forks[i];
		(*info)->philo[i].l_fork = &(*info)->forks[(i + 1) % (*info)->number_of_philos];
		// printf("Philo number %d => \n", i + 1);
		// printf("Right fork => [%p] \n", (*info)->philo[i].r_fork);
		// printf("Left fork => [%p] \n", (*info)->philo[i].l_fork);
	}
}

void	save_data(char **av, t_info **info)
{
	(*info)->number_of_philos = my_atoi(av[1]);
	(*info)->time_to_die = my_atoi(av[2]);
	(*info)->time_to_eat = my_atoi(av[3]);
	(*info)->time_to_sleep = my_atoi(av[4]);
	if (av[5])
		(*info)->nmbr_times_to_eat = my_atoi(av[5]);
	else
		(*info)->nmbr_times_to_eat = -1;
}

void	parsing(char **av, t_info **info)
{
	int	i;

	i = 1;
	// pthread_mutex_lock(&g_lock);
	// pthread_mutex_unlock(&g_lock);
	// pthread_mutex_init(&g_lock, NULL);
	while (av[i])
	{
		check_empty(av[i]);
		check_valid(av[i]);
		i++;
	}
	(*info) = malloc(sizeof(t_info));
	if (!*info)
		ft_putstr_fd("Malloc failed", 2);
	save_data(av, info);
	init_philo(info);
}
