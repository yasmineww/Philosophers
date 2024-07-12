/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:08:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/12 10:30:52 by ymakhlou         ###   ########.fr       */
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
	int	number_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nmbr_times_to_eat;
}	t_philo;

int		ft_isdigit(int c);
int		ft_strlen(char	*av);
int		my_atoi(char *str);
void	parsing(char **av, t_philo **philo);
void	ft_putstr_fd(char *s, int fd);

#endif