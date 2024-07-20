/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:08:41 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/20 17:04:40 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
		return (1);
	printf(" %d has taken a fork", philo->id);
	if (pthread_mutex_lock(philo->l_fork))
		return (1);
	printf(" %d has taken a fork", philo->id);
	printf(" %d is eating\n", philo->id);
	usleep(philo->info->time_to_eat * 1000);
	if (pthread_mutex_unlock(philo->r_fork))
		return (1);
	if (pthread_mutex_unlock(philo->l_fork))
		return (1);
	return (0);
}

int	start_routine(void *philo_x)
{
	t_philo	*philo;

	philo = (t_philo *)philo_x;
	while (1)
	{
		if (!eating(philo))
			return (1);
		philo->meal += 1;
		// philo->last_meal = get_time();ms
		printf(" %d is sleeping", philo->id);
		usleep(philo->info.time_to_sleep * 1000);
		printf(" %d is thinking", philo->id);
	}
	return (0);
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
		usleep(info->time_to_eat * 1000);
		i++;
	}
}

int	create_monitor(t_info *info)
{
	while (1)
	{
		if (death_check(info->philo) || full_check(info->philo))
			break ;
	}
}

void	simulation(t_info *info)
{
	create_threads(info);
	create_monitor(info);
}
