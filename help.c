/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:33:31 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/22 23:05:51 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//here i malloc memory for storing things for content of a struct, and
//create a list that technically store the same struct and return pointer at
// end of list

void	*malloc_table_sth(t_table *pp, size_t size)
{
	void	*pt;
	t_list	*elements;

	pt = malloc(size);
	if (!pt)
		return (NULL);
	elements = malloc(sizeof(t_list));
	if (!elements)
	{
		free(pt);
		return (NULL);
	}
	elements->now = pt;
	elements->front = pp->garbabe_location;
	pp->garbabe_location = elements;
	return (pt);
}

size_t	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000L) + (time.tv_usec / 1000));
}

int	eat_gap(t_table *pp, int id)
{
	size_t	now;
	int	hunger_time;

	now = get_time_ms();
	hunger_time = now - pp->philop[id].last_time_eat;
	return (hunger_time);
}
//1 = takefork; 2 = eating; 3 = sleeping; 4 = thinking; 5 = died

void	o_print(t_philop *pp, int i, int id)
{
	int	time;

	time = (get_time_ms() - pp->table->start_time);
	pthread_mutex_lock(&pp->table->p_lock);
	if (pp->table->someone_died && i != 5)
	{
		pthread_mutex_unlock(&pp->table->p_lock);
		return ;
	}
	if (i == 1)
		printf("%d %d has taken a fork\n", time, (id));
	else if (i == 2)
		printf("%d %d is eating\n", time, (id));
	else if (i == 3)
		printf("%d %d is sleeping\n", time, (id));
	else if (i == 4)
		printf("%d %d is thinking\n", time, (id));
	else if (i == 6)
		printf("%d Everyone is full\n", time);
	else if (i == 5)
	{
		pthread_mutex_lock(&pp->table->death);
		if (!pp->table->someone_died)
			pp->table->someone_died = true;
		printf("%d %d died\n", time, (id));
		pthread_mutex_unlock(&pp->table->death);
	}
	pthread_mutex_unlock(&pp->table->p_lock);
}

void	smart_rest(t_philop *pp, size_t i)
{
	size_t	now;
	bool	state;

	now = get_time_ms();
	while (get_time_ms() - now < i)
	{
		pthread_mutex_lock(&pp->table->death);
		state = pp->table->someone_died;
		pthread_mutex_unlock(&pp->table->death);
		if (state)
			return ;
		usleep(10);
	}
}

