/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:24:33 by yuerliu           #+#    #+#             */
/*   Updated: 2025/07/22 23:21:06 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start the routine

int	feast_time(t_table *pp)
{
	int			i;
	pthread_t	td;

	i = 0;
	pp->start_time = get_time_ms();
	while (i < pp->head)
	{
		pthread_create(&pp->philop[i].thread, NULL, life_of_philop,
			&pp->philop[i]);
		i++;
	}
	i = 0;
	pthread_create(&td, NULL, dead_yet, pp);
	while (i < pp->head)
	{
		pthread_join(pp->philop[i].thread, NULL);
		i++;
	}
	pthread_join(td, NULL);
	return (1);
}

void	*life_of_philop(void *pp)
{
	t_philop	*philop;
	bool		state;

	philop = (t_philop *)pp;
	if (pp == NULL)
		return (NULL);
	if (philop->table->someone_died == true)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philop->table->death);
		state = philop->table->someone_died;
		pthread_mutex_unlock(&philop->table->death);
		if (state)
			return (NULL);
		if (philop->eat_count == philop->table->min_times_to_eat)
    		philop->full = 1;
		if (philop->full == 1)
			return (NULL);
		eat(philop);
		p_sleep(philop);
		thinking(philop);
	}
	return (NULL);
}

//have to set checking_dead in the routine. so philops exit in time
void	*dead_yet(void *pp)
{
	int		id;
	t_table	*eye;

	eye = (t_table *)pp;
	while (eye->someone_died != true)
	{
		id = 0;
		while (id < eye->head && eye->someone_died != true)
		{
			if (eat_gap(eye, id) > eye->die_time)
			{
				pthread_mutex_lock(&eye->death);
				eye->someone_died = true;
				pthread_mutex_unlock(&eye->death);
				return (o_print(&eye->philop[id], 5, id + 1), NULL);
			}
			id++;
		}
		if (we_r_full(eye) == 0)
			return (o_print(&eye->philop[0], 6, 1), NULL);
		usleep(10);
	}
	return (NULL);
}

int	we_r_full(t_table *pp)
{
	int	id;

	id = 0;
	if (pp->min_times_to_eat <= -1)
		return (1);
	while (id < pp->head)
	{
		// if (pp->philop[id].eat_count < pp->min_times_to_eat)
		// 	return (1);
		// if (pp->philop[id].eat_count == pp->min_times_to_eat)
		// 	pp->philop[id].full = 1;
		if (pp->philop[id].full == 0)
			return (1);
		id++;
	}
	return (0);
}
