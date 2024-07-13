/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:14:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/13 10:36:06 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_info	*info;

	atexit(f);
	info = NULL;
	if (ac == 5 || ac == 6)
	{
		parsing(av, &info);
		printf("number_of_philos = %d\n", info->number_of_philos);
		printf("time_to_die = %d\n", info->time_to_die);
		printf("time_to_eat = %d\n", info->time_to_eat);
		printf("time_to_sleep = %d\n", info->time_to_sleep);
		// int i = info->number_of_philos;
		// while (i > 0)
		// {
		// 	printf("id = %d\n", info->philo[i - 1].id);
		// 	printf("meal = %d\n", info->philo[i - 1].meal);
		// 	// printf("l_fork = %d\n", info->philo[i - 1].l_fork);
		// 	i--;
		// }
		if (ac == 6)
			printf("nmbr_times_to_eat = %d\n", info->nmbr_times_to_eat);
	}
	else
		ft_putstr_fd("Wrong number of arguments", 2);
	return (0);
}
