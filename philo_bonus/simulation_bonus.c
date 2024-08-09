/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:37:18 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/09 13:51:37 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_print(t_info *info, char *str)
{
	sem_wait(info->print);
	printf("%ld %d %s\n", get_time() - info->time, info->id, str);
	sem_post(info->print);
}

void	eating(t_info **info)
{
	sem_wait((*info)->forks);
	my_print((*info), "has taken a fork");
	sem_wait((*info)->forks);
	my_print((*info), "has taken a fork");
	my_print((*info), "is eating");
	(*info)->last_meal = get_time();
	my_usleep((*info)->time_to_eat);
	(*info)->meal += 1;
	sem_post((*info)->forks);
	sem_post((*info)->forks);
}

void	routine(t_info *info)
{
	int	i;

	i = info->must_eat;
	if (info->id % 2 == 1)
		usleep(200);
	while (i)
	{
		eating(&info);
		my_print(info, "is sleeping");
		my_usleep(info->time_to_sleep);
		my_print(info, "is thinking");
		i--;
	}
}

void	*guardian(void *inf)
{
	t_info	*info;
	
	info = (t_info *)inf;	
	while (1)
	{
		if (get_time() - info->last_meal >= info->time_to_die)
		{
			sem_wait(info->print);
			printf("%ld %d died\n", get_time() - info->time, info->id);
			exit(EXIT_DEATH);
		}
		else if (info->meal == info->must_eat)
		{
			puts("ok");
			exit(EXIT_FULL);
		}
	}
}

int	simulation(t_info *info)
{
	pid_t	*pid;
	int		i;
	int		counter;
	int		exit_status;

	i = -1;
	pid = malloc(sizeof(pid_t) * info->number_of_philosophers);
	if (!pid)
		return (ft_putstr_fd("Malloc failed!", 2), 1);
	info->time = get_time();
	while (++i < info->number_of_philosophers)
	{
		pid[i] = fork();
		info->last_meal = get_time();
		if (pid[i] == 0)
		{
			info->id = i + 1;
			info->last_meal = get_time();
			if (pthread_create(&info->thread, NULL, guardian, info))
			{
				free(pid);
				ft_putstr_fd("Thread creation failed!", 2);
				exit(EXIT_FAILURE);
			}
			routine(info);
		}
		else if (pid[i] == -1)
			return (ft_putstr_fd("Fork failed!", 2), 1);
	}
	i = -1;
	counter = 0;
	exit_status = 0;
	waitpid(-1, &exit_status, 0);
	printf("exit_status = %d\n", exit_status);
	if (exit_status == EXIT_DEATH)
	{
		puts("here");
		while (++i < info->number_of_philosophers)
			kill(pid[i], SIGKILL);
		free(pid);
	}
	else if (exit_status == EXIT_FULL)
	{
		printf("counter = %d\n", counter);
		if (counter != info->number_of_philosophers)
			counter++;
		else if (counter == info->number_of_philosophers)
			return (free(pid), 0);
		waitpid(-1, &exit_status, 0);
	}
	free(pid);
	return (0);
}
