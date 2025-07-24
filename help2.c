/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:26:25 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/19 20:13:10 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up(t_list *garbabe)
{
	t_list	*temp;

	while (garbabe != NULL)
	{
		temp = garbabe;
		garbabe = garbabe->front;
		free(temp->now);
		free(temp);
	}
}

//1 = ok, 0 != ok;

int	ok_input(int ac, char **av)
{
	int	i;
	int	h;

	i = 1;
	if (ac != 5 && ac != 6)
		return (0);
	while (i < (ac - 1))
	{
		h = 0;
		while (av[i][h])
		{
			if (ft_isdigit(av[i][h]) == 0)
				return (0);
			h++;
		}
		i++;
	}
	if (zero(ac, av) == 0)
		return (0);
	return (1);
}

int	ft_isdigit(int num)
{
	if (num >= '0' && num <= '9')
		return (1);
	else
		return (0);
}

int	zero(int ac, char **av)
{
	int	i;

	i = 1;
	while (i <= ac - 1)
	{
		if (ft_atoi(av[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || ((str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
