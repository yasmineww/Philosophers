/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:14:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 11:21:47 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	f()
// {
// 	system("leaks philo");
// }

void	free_leaks(t_info *info)
{
	free(info->philo);
	free(info->forks);
	free(info);
}

int	main(int ac, char **av)
{
	t_info	*info;

	// atexit(f);
	info = NULL;
	if (ac == 5 || ac == 6)
	{
		if (parsing(av, &info))
			return (1);
		if (info->total_philos == 0 || info->must_eat == 0)
			return (0);
		simulation(info);
		free_leaks(info);
		return (0);
	}
	ft_putstr_fd("Wrong number of arguments!", 2);
	return (1);
}
