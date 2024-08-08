/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:36:11 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 18:58:58 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct s_info
{
	sem_t		forks;
	sem_t		print;
	pthread_t	thread;
	size_t		last_meal;
	int			id;
	int			meal;
	int			number_of_philosophers;
	size_t		time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	size_t		time;
	int			full;
}	t_info;

int		parsing(char **av, t_info **info);
int		save_data(char **av, t_info **info);
int		init_data(t_info **info);
int		check_valid(char *av);
void	free_leaks(t_info *info);
int		simulation(t_info *info);

#endif