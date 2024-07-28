/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:08:41 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/28 18:06:18 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo **philo)
{
	if (pthread_mutex_lock((*philo)->r_fork))
		return (1);
	printf("%d %d has taken a fork\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	if (pthread_mutex_lock((*philo)->l_fork))
		return (1);
	printf("%d %d has taken a fork\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	printf("%d %d is eating\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	(*philo)->last_meal = get_current_time();
	(*philo)->meal += 1;
	usleep((*philo)->info->time_to_eat * 1000);
	if (pthread_mutex_unlock((*philo)->l_fork) == -1)
		return (1);
	if (pthread_mutex_unlock((*philo)->r_fork))
		return (1);
	return (0);
}

void	*start_routine(void *philo_x)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_x;
	i = philo->info->must_eat;
	if (philo->id % 2 == 1)
		usleep(200);
	while (i)
	{
		if (eating(&philo))
			return (NULL);
		printf("%d %d is sleeping\n",get_current_time() - philo->info->time, philo->id);
		usleep(philo->info->time_to_sleep * 1000);
		printf("%d %d is thinking\n",get_current_time() - philo->info->time, philo->id);
		if (get_current_time() - philo->last_meal >= philo->info->time_to_die)
		{
			philo->info->death = -1;
			printf("%d %d died\n",get_current_time() - philo->info->time, philo->id);
			exit (1);
		}
		i--;
	}
	return NULL;
}

int	create_threads(t_info *info)
{
	int	i;

	i = 0;
	info->time = get_current_time();
	while (i < info->total_philos)
	{
		if (pthread_create(&info->philo[i].thread, NULL, start_routine,
				&info->philo[i]))
		{
			ft_putstr_fd("Thread creation failed!", 2);
			return (1);
		}
		// usleep(info->time_to_eat * 1000);
		i++;
	}
	while (info->death == 0)
	{
	}
	return (0);
}

void	simulation(t_info *info)
{
	create_threads(info);
}
