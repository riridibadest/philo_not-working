/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:24:33 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/19 22:56:09 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start the routine

void	feast_time(t_table *pp)
{
	int			i;
	pthread_t	td;

	i = 0;
	pp->start_time = get_time_ms();
	while (i < pp->head)
	{
		if (pthread_create(&pp->philop[i].thread, NULL, life_of_philop,
				&pp->philop[i]) != 0)
		{
			perror("pthread_create");
			pp->someone_died = true;
			return ;
		}
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
}

void	*life_of_philop(void *pp)
{
	t_philop	*philop;

	philop = (t_philop *)pp;
	if (philop->table->someone_died == true)
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&philop->table->death);
		if (philop->table->someone_died)
			return (pthread_mutex_unlock(&philop->table->death), NULL);
		pthread_mutex_unlock(&philop->table->death);
		if (philop->full == 1)
			return (NULL);
		eat(philop);
		p_sleep(philop);
		thinking(philop);
	}
	return (NULL);
}

// have to set checking_dead in the routine. so philops exit in time
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
			if (we_r_full(eye) == 0)
				return (o_print(&eye->philop[0], 6, 1), NULL);
			if (eat_gap(eye, id) >= (size_t)eye->die_time)
			{
				pthread_mutex_lock(&eye->death);
				eye->someone_died = true;
				pthread_mutex_unlock(&eye->death);
				return (o_print(&eye->philop[id], 5, id + 1), NULL);
			}
			id++;
		}
		usleep(500);
	}
	return (NULL);
}
//this is gemini:

// void	*dead_yet(void *pp)
// {
// 	int		id;
// 	t_table	*eye;

// 	eye = (t_table *)pp;
// 	while (eye->someone_died != true)
// 	{
//         // 1. **PRIORITIZE THE FULL CHECK**
// 		if (we_r_full(eye) == 0)
// 		{
//             // Set the death flag to cleanly stop all philop threads
//             pthread_mutex_lock(&eye->death);
// 			eye->someone_died = true; 
//             pthread_mutex_unlock(&eye->death);
            
//             // Print the success message and return
// 			return (o_print(&eye->philop[0], 6, 1), NULL);
// 		}
        
//         // 2. Begin Death Monitoring Loop
// 		id = 0;
// 		while (id < eye->head && eye->someone_died != true)
// 		{
//             // Check for death (only if not already stopped by 'full' check)
// 			if (eat_gap(eye, id) >= (size_t)eye->die_time)
// 			{
// 				pthread_mutex_lock(&eye->death);
// 				eye->someone_died = true;
// 				pthread_mutex_unlock(&eye->death);
// 				return (o_print(&eye->philop[id], 5, id + 1), NULL);
// 			}
// 			id++;
// 		}
// 		usleep(100); // Or whatever low value you decided on (e.g., 500)
// 	}
// 	return (NULL);
// }

// void	*dead_yet(void *pp)
// {
// 	int		id;
// 	t_table	*eye;

// 	eye = (t_table *)pp;
// 	while (1)
// 	{
// 		id = 0;
// 		while (id < eye->head && eye->someone_died != true)
// 		{
// 			pthread_mutex_lock(&eye->death);
// 			// if (eye->someone_died)
// 			// {
// 			// 	pthread_mutex_unlock(&eye->death);
// 			// 	return (NULL);
// 			// }
// 			if (we_r_full(eye) == 0)
// 			{
// 				eye->someone_died = true;
// 				o_print(&eye->philop[0], 6, 1);
// 				pthread_mutex_unlock(&eye->death);
// 				return (NULL);
// 			}
// 			if (eat_gap(eye, id) >= (size_t)eye->die_time)
// 			{
// 				eye->someone_died = true;
// 				o_print(&eye->philop[id], 5, id + 1);
// 				pthread_mutex_unlock(&eye->death);
// 				return (NULL);
// 			}
// 			pthread_mutex_unlock(&eye->death);
// 			id++;
// 		}
// 		usleep(500);
// 	}
// 	return (NULL);
// }

int	we_r_full(t_table *pp)
{
	int	id;

	//pthread_mutex_lock(&pp->death);
	id = 0;
	if (pp->min_times_to_eat <= -1)
		return (1);
	while (id < pp->head)
	{
		if (pp->philop[id].full == 0)
			return 1;
			// return (pthread_mutex_unlock(&pp->death), 1);
		id++;
	}
	//pthread_mutex_unlock(&pp->death);
	return (0);
}
