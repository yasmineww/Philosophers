/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:08:41 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 11:51:09 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_print(int timestamp, int id, char *str, t_info *info)
{
	pthread_mutex_lock(&info->print);
	if (info->death == -1)
	{
		printf("%d %d %s\n", timestamp, id, str);
		return ;
	}
	printf("%d %d %s\n", timestamp, id, str);
	pthread_mutex_unlock(&info->print);
}

void	eating(t_philo **philo)
{
	pthread_mutex_lock((*philo)->r_fork);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "has taken a fork", (*philo)->info);
	pthread_mutex_lock((*philo)->l_fork);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "has taken a fork", (*philo)->info);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "is eating", (*philo)->info);
	pthread_mutex_lock(&(*philo)->info->lock_death);
	(*philo)->last_meal = get_current_time();
	pthread_mutex_unlock(&(*philo)->info->lock_death);
	ft_usleep((*philo)->info->time_to_eat);
	(*philo)->meal += 1;
	pthread_mutex_unlock((*philo)->r_fork);
	pthread_mutex_unlock((*philo)->l_fork);
	if ((*philo)->meal == (*philo)->info->must_eat)
	{
		pthread_mutex_lock(&(*philo)->info->lock_full);
		(*philo)->info->full++;
		pthread_mutex_unlock(&(*philo)->info->lock_full);
	}
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
		eating(&philo);
		my_print(get_current_time() - philo->info->time, philo->id, "is sleeping", philo->info);
		ft_usleep(philo->info->time_to_sleep);
		my_print(get_current_time() - philo->info->time, philo->id, "is thinking", philo->info);
		i--;
	}
	return (NULL);
}

void	guardian(t_info *info)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&info->lock_death);
		if (get_current_time() - info->philo[i].last_meal >= info->time_to_die)
		{
			pthread_mutex_lock(&info->lock_full);
			info->death = -1;
			pthread_mutex_unlock(&info->lock_full);
			my_print(get_current_time() - info->time, info->philo[i].id, "died", info);
			break ;
		}
		pthread_mutex_lock(&info->lock_full);
		if (info->full == info->total_philos)
			break ;
		pthread_mutex_unlock(&info->lock_full);
		pthread_mutex_unlock(&info->lock_death);
		if (++i == info->total_philos)
			i = 0;
	}
}

int	simulation(t_info *info)
{
	int	i;

	i = 0;
	info->time = get_current_time();
	while (i < info->total_philos)
	{
		info->philo[i].last_meal = get_current_time();
		if (pthread_create(&info->philo[i].thread, NULL, start_routine,
				&info->philo[i]))
		{
			ft_putstr_fd("Thread creation failed!", 2);
			return (1);
		}
		if (pthread_detach(info->philo[i].thread))
			return (ft_putstr_fd("Thread detach failed!", 2), 1);
		i++;
	}
	guardian(info);
	return (0);
}
