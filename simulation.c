/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:08:41 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 18:52:38 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_routine(void *info)
{
	t_info *philo;
	
	philo = (t_info *)info;
	// 
}

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_create(info->philo[i].thread, NULL, start_routine,
				&info->philo[i]))
		{
			ft_putstr_fd("Thread creation failed!", 2);
			return (1);
		}
		i++;
	}
		// if (pthread_join())
	
}

void	simulation(t_info *info)
{
	create_threads(info);
}
