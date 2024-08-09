/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 16:37:18 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/09 16:38:04 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	my_print(t_info *info, char *str)
{
	sem_wait(info->print);
	printf("%ld %d %s\n", get_time() - info->time, info->id, str);
	sem_post(info->print);
}

void	routine(t_info *info)
{
	int	i;

	i = info->must_eat;
	if (info->id % 2 == 1)
		usleep(200);
	while (i)
	{
		sem_wait(info->forks);
		my_print(info, "has taken a fork");
		sem_wait(info->forks);
		my_print(info, "has taken a fork");
		my_print(info, "is eating");
		info->last_meal = get_time();
		my_usleep(info->time_to_eat);
		info->meal += 1;
		sem_post(info->forks);
		sem_post(info->forks);
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
			exit(EXIT_FULL);
	}
}

int	wait_child_process(t_info *info, pid_t *pid)
{
	int	i;
	int	counter;
	int	exit_status;

	i = -1;
	counter = 1;
	exit_status = 0;
	waitpid(-1, &exit_status, 0);
	if (exit_status == EXIT_DEATH)
	{
		while (++i < info->number_of_philosophers)
			kill(pid[i], SIGKILL);
	}
	else if (exit_status == EXIT_FULL)
	{
		while (counter < info->number_of_philosophers)
		{
			counter++;
			waitpid(-1, &exit_status, 0);
		}
	}
	free(pid);
	return (0);
}

int	simulation(t_info *info)
{
	pid_t	*pid;
	int		i;

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
				return(free(pid), ft_putstr_fd("Thread creation failed!", 2), 1);
			routine(info);
		}
		else if (pid[i] == -1)
			return (ft_putstr_fd("Fork failed!", 2), 1);
	}
	wait_child_process(info, pid);
	return (0);
}
