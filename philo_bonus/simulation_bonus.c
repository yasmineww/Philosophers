/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:37:18 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 19:01:25 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_print(t_info *info, char *str)
{
	sem_wait(info->print);
	printf("%ld %d %s\n", get_time() - info->time, info->id, str);
	sem_post(info->print);
}

void	eating(t_info *info)
{
	sem_wait(info->forks);
	my_print(info, "has taken a fork");
	sem_wait(info->forks);
	my_print(info, "has taken a fork");
	my_print(info, "is eating");
	info->last_meal = get_time();
	ft_usleep(info->time_to_eat);
	info->meal += 1;
	sem_post(info->forks);
	sem_post(info->forks);
	if (info->meal == info->must_eat)
		info->full += 1;
}

void	routine(t_info *info)
{
	int	i;

	i = info->must_eat;
	if (info->id % 2 == 1)
		usleep(200);
	while (i)
	{
		eating(info);
		my_print(info, "is sleeping");
		ft_usleep(info->time_to_sleep);
		my_print(info, "is thinking");
		i--;
	}
}

void	guardian(t_info *info)
{
	while (1)
	{
		if (get_time() - info->last_meal >= info->time_to_die)
		{
			sem_wait(info->print);
			printf("%ld %d died\n", get_time() - info->time, info->id);
			break ;
		}
		else if (info->full == info->number_of_philosophers)
			break ;
	}
}

int	simulation(t_info *info)
{
	int		i;
	pid_t	*pid;

	i = 0;
	info->time = get_time();
	while (i < info->number_of_philosophers)
	{
		pid[i] = fork();
		info->last_meal = get_time();
		if (pid[i] == 0)
		{
			info->id = i + 1;
			info->last_meal = get_time();
			if (pthread_create(&info->thread, NULL, guardian, &info))
				return (ft_putstr_fd("Thread creation failed!", 2), 1);
			routine(info);
		}
		else if (pid[i] == -1)
			return (ft_putstr_fd("Fork failed!", 2), 1);
		i++;
	}
	return (0);
}