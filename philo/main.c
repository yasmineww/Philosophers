/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:14:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/13 15:59:18 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	free(info->philo);
	free(info->forks);
	free(info);
}

void	free_leaks(t_info *info)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->lock_death);
	pthread_mutex_destroy(&info->lock_full);
	while (i < info->number_of_philosophers)
	{
		pthread_mutex_destroy(info->philo[i].r_fork);
		pthread_mutex_destroy(info->philo[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(info->forks);
	free(info->philo);
	free(info->forks);
	free(info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	info = NULL;
	if (ac == 5 || ac == 6)
	{
		if (parsing(av, &info))
			return (1);
		if (info->number_of_philosophers == 0 || info->must_eat == 0)
			return (free_leaks(info), 0);
		simulation(info);
		free_leaks(info);
		return (0);
	}
	ft_putstr_fd("Wrong number of arguments!", 2);
	return (1);
}
