/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lma.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 00:12:25 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/22 16:28:11 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_check(t_table *pp)
{
	pthread_mutex_lock(&pp->death);
	if (pp->someone_died)
		return (pthread_mutex_unlock(&pp->death), 1);
	return (pthread_mutex_unlock(&pp->death), 0);
}

void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	if (!table || table->head <= 0)
		return ;

	// Destroy standalone mutexes
	pthread_mutex_destroy(&table->death);
	pthread_mutex_destroy(&table->p_lock);

	// Destroy fork mutexes
	while (i < table->head)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}
