/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:08:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 18:01:02 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	struct s_info	*info;
	int				meal;
	int				id;
}	t_philo;

typedef struct s_info
{
	t_philo				*philo;
	pthread_mutex_t		*forks;
	int					total_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nmbr_times_to_eat;
}	t_info;

int		ft_isdigit(int c);
int		ft_strlen(char	*av);
int		my_atoi(char *str);
int		parsing(char **av, t_info **philo);
void	ft_putstr_fd(char *s, int fd);

#endif