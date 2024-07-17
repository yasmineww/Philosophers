/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:14:05 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/17 11:33:30 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	f()
// {
// 	system("leaks philo");
// }

int	main(int ac, char **av)
{
	t_info	*info;

	// atexit(f);
	info = NULL;
	if (ac == 5 || ac == 6)
	{
		if (parsing(av, &info))
			return (1);
		// simulation();
		free(info->philo);
		free(info->forks);
		free(info);
		return (0);
	}
	ft_putstr_fd("Wrong number of arguments!", 2);
	return (1);
}
