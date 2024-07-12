/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:14:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/12 10:31:07 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f()
{
	system("leaks philo");
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	atexit(f);
	philo = NULL;
	if (ac == 5 || ac == 6)
	{
		parsing(av, &philo);
		printf("number_of_philos = %d\n", philo->number_of_philos);
		printf("time_to_die = %d\n", philo->time_to_die);
		printf("time_to_eat = %d\n", philo->time_to_eat);
		printf("time_to_sleep = %d\n", philo->time_to_sleep);
		if (ac == 6)
			printf("nmbr_times_to_eat = %d\n", philo->nmbr_times_to_eat);
	}
	else
		ft_putstr_fd("Wrong number of arguments", 2);
	return (0);
}
