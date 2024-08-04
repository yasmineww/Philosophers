/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:08:41 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/04 16:56:11 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_print(int timestamp, int id, char *str, t_info *info)
{
	if (info->death == -1 || info->full == info->total_philos)
		return ;
	pthread_mutex_lock(&info->print);
	printf("%d %d %s\n", timestamp, id, str);
	pthread_mutex_unlock(&info->print);
}

int	eating(t_philo **philo)
{
	pthread_mutex_lock((*philo)->r_fork);
		// return (ft_putstr_fd("Mutex lock failed!", 2), 1);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "has taken a fork", (*philo)->info);
	// printf("%d %d has taken a fork\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	pthread_mutex_lock((*philo)->l_fork);
		// return (ft_putstr_fd("Mutex lock failed!", 2), 1);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "has taken a fork", (*philo)->info);
	my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "is eating", (*philo)->info);
	// printf("%d %d has taken a fork\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	// printf("%d %d is eating\n",get_current_time() - (*philo)->info->time, (*philo)->id);
	(*philo)->meal += 1;
	usleep((*philo)->info->time_to_eat * 1000);
	(*philo)->last_meal = get_current_time();
	pthread_mutex_unlock((*philo)->r_fork);
		// return (ft_putstr_fd("Mutex unlock failed!", 2), 1);
	pthread_mutex_unlock((*philo)->l_fork);
		// return (ft_putstr_fd("Mutex unlock failed!", 2), 1);
	if ((*philo)->meal == (*philo)->info->must_eat)
	{
		pthread_mutex_lock(&(*philo)->info->print);
		(*philo)->info->full++;
		pthread_mutex_unlock(&(*philo)->info->print);
	}
	return (0);
}

int	one_philo(t_philo **philo)
{
	if ((*philo)->info->total_philos == 1)
	{
		my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "has taken a fork", (*philo)->info);
		// printf("%d %d has taken a fork\n",get_current_time() - (*philo)->info->time, (*philo)->id);
		my_print(get_current_time() - (*philo)->info->time, (*philo)->id, "died", (*philo)->info);
		// printf("%d %d died\n",get_current_time() - (*philo)->info->time, (*philo)->id);
		(*philo)->info->death = -1;
		return (1);
	}
	return (0);
}

void	*start_routine(void *philo_x)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philo_x;
	if (one_philo(&philo))
		return (NULL);
	i = philo->info->must_eat;
	if (philo->id % 2 == 1)
		usleep(100);
	while (i)
	{
		if (eating(&philo))
			return (NULL);
		my_print(get_current_time() - philo->info->time, philo->id, "is sleeping", philo->info);
		// printf("%d %d is sleeping\n",get_current_time() - philo->info->time, philo->id);
		usleep(philo->info->time_to_sleep * 1000);
		if (get_current_time() - philo->last_meal >= philo->info->time_to_die)
		{
			philo->info->death = -1;
			my_print(get_current_time() - philo->info->time, philo->id, "died", philo->info);
			// printf("%d %d died\n",get_current_time() - philo->info->time, philo->id);
			return (NULL);
		}
		my_print(get_current_time() - philo->info->time, philo->id, "is thinking", philo->info);
		// printf("%d %d is thinking\n",get_current_time() - philo->info->time, philo->id);
		i--;
	}
	return (NULL);
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
		i++;
	}
	i = 0;
	while (i < info->total_philos)
	{
		if (pthread_detach(info->philo[i].thread))
			return (ft_putstr_fd("Thread detach failed!", 2), 1);
		i++;
	}
	while (info->death != -1)
	{
	}
	return (0);
}

void	simulation(t_info *info)
{
	create_threads(info);
}
