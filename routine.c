/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:44 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/19 22:55:11 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philop *pp, size_t id)
{
	pthread_mutex_lock(&pp->table->death);
	if (pp->table->someone_died)
	{
		pthread_mutex_unlock(&pp->table->death);
		return ;
	}
	pthread_mutex_unlock(&pp->table->death);
	if ((id % 2) == 1)
	{
		pthread_mutex_lock(pp->l_fork);
		o_print(pp, 1, id);
		pthread_mutex_lock(pp->r_fork);
		o_print(pp, 1, id);
	}
	else
	{
		pthread_mutex_lock(pp->r_fork);
		o_print(pp, 1, id);
		pthread_mutex_lock(pp->l_fork);
		o_print(pp, 1, id);
	}
}

int	eat(t_philop *pp)
{
	size_t	id;

	id = pp->id;
	if (pp->table->head == 1)
		return (solo_eating(pp), 0);
	if (pp->table->someone_died)
		return (0);
	take_forks(pp, id);
	o_print(pp, 2, id);
	pthread_mutex_lock(&pp->table->death);
	pp->last_time_eat = get_time_ms();
	pthread_mutex_unlock(&pp->table->death);
	pp->eat_count++;
	if (pp->eat_count == pp->table->min_times_to_eat)
		pp->full = 1;
	smart_rest(pp, pp->table->eat_time);
	if (id % 2 == 1)
	{
		pthread_mutex_unlock(pp->r_fork);
		pthread_mutex_unlock(pp->l_fork);
	}
	else
	{
		pthread_mutex_unlock(pp->l_fork);
		pthread_mutex_unlock(pp->r_fork);
	}
	return (1);
}

void	p_sleep(t_philop *pp)
{
	bool	state;

	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	if (pp->full == 1)
		return ;
	o_print(pp, 3, pp->id);
	smart_rest(pp, pp->table->sleep_time);
}

void	thinking(t_philop *pp)
{
	bool	state;

	pthread_mutex_lock(&pp->table->death);
	state = pp->table->someone_died;
	pthread_mutex_unlock(&pp->table->death);
	if (state)
		return ;
	if (pp->full == 1)
		return ;
	o_print(pp, 4, pp->id);
}

void	solo_eating(t_philop *pp)
{
	int	id;

	id = pp->id;
	pthread_mutex_lock(pp->r_fork);
	o_print(pp, 1, id);
	smart_rest(pp, pp->table->die_time);
	pthread_mutex_unlock(pp->r_fork);
	pthread_mutex_lock(&pp->table->death);
	pp->table->someone_died = true;
	pthread_mutex_unlock(&pp->table->death);
	o_print(pp, 5, id);
}
