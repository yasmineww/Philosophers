/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymakhlou <ymakhlou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:04:00 by ymakhlou          #+#    #+#             */
/*   Updated: 2024/07/05 18:27:07 by ymakhlou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	syntax_error(int ac, char **av, t_philo *philo)
{
	int	i;

	i = 0;
	if (av[0])
	//ft_strlen to input then is digit in a while loop
	else if (ac = 6)
	{
		
	}
	while (i < ac - 1)
	{
		if (av[i])
	}
}

void	parsing(int ac, char **av, t_philo **philo)
{
	(*philo)->id = my_atoi(av[0]);
	if (ac == 6)
		(*philo)->eat_nb = my_atoi(av[4]);
	if (syntax_error(ac, av, philo))
	{
		printf("Error: Syntax error\n");
		exit(1);
	}
}
