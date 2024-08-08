/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:35:25 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/08/08 19:00:34 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_leaks(t_info *info)
{
	sem_close(info->print);
	sem_close(info->forks);
	sem_unlink("/forks");
	sem_unlink("/print");
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
		simulation(info);
		free_leaks(info);
		return (0);
	}
	ft_putstr_fd("Wrong number of arguments!", 2);
	return (1);
}
