/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:08:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 12:43:17 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_info	t_info;

typedef struct s_philo
{
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	struct s_info	*info;
	int				meal;
	int				id;
	size_t			last_meal;
}	t_philo;

typedef struct s_info
{
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		lock_death;
	pthread_mutex_t		lock_full;
	int					number_of_philosophers;
	size_t				time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	size_t				time;
	int					full;
}	t_info;

int		ft_isdigit(int c);
int		ft_strlen(char	*av);
int		my_atoi(char *str);
int		parsing(char **av, t_info **philo);
void	ft_putstr_fd(char *s, int fd);
int		simulation(t_info *info);
size_t	get_time(void);
int		my_usleep(size_t milliseconds);
void	free_leaks(t_info *info);
int		check_empty(char *av);

#endif