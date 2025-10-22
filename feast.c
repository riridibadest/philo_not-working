/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   feast.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:24:33 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/22 21:06:23 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// start the routine

// void	feast_time(t_table *pp)
// {
// 	int			i;
// 	pthread_t	td;

// 	i = 0;
// 	pp->start_time = get_time_ms();
// 	while (i < pp->head)
// 	{
// 		if (pthread_create(&pp->philop[i].thread, NULL, life_of_philop,
// 				&pp->philop[i]) != 0)
// 		{
// 			perror("pthread_create");
// 			pp->someone_died = true;
// 			return ;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	pthread_create(&td, NULL, dead_yet, pp);
// 	while (i < pp->head)
// 	{
// 		pthread_join(pp->philop[i].thread, NULL);
// 		i++;
// 	}
// 	pthread_join(td, NULL);
// }

// void	*life_of_philop(void *pp)
// {
// 	t_philop	*philop;

// 	philop = (t_philop *)pp;
// 	if (death_check(philop->table) == 1)
// 		return (NULL);
// 	if (philop->id % 2 == 0)
// 		usleep(100);
// 	while (1)
// 	{
// 		if (death_check(philop->table) == 1)
// 			return (NULL);
// 		if (philop->full == 1)
// 			return (NULL);
// 		// if (eat(philop) == 0)
// 		// 	return (NULL);
// 		eat(philop);
// 		p_sleep(philop);
// 		thinking(philop);
// 	}
// 	return (NULL);
// }
// //my verison
// // have to set checking_dead in the routine. so philops exit in time
// void	*dead_yet(void *pp)
// {
// 	int		id;
// 	t_table	*eye;

// 	eye = (t_table *)pp;
// 	while (1)
// 	{
// 		if (we_r_full(eye) == 0)
// 			return (o_print(&eye->philop[0], 6, 1), NULL);
// 		id = 0;
// 		while (id < eye->head && eye->someone_died != true)
// 		{
// 			if (eat_gap(eye, id) >= (size_t)eye->die_time)
// 			{
// 				pthread_mutex_lock(&eye->death);
// 				eye->someone_died = true;
// 				pthread_mutex_unlock(&eye->death);
// 				return (o_print(&eye->philop[id], 5, id + 1), NULL);
// 			}
// 			id++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }

// // void	*dead_yet(void *pp)
// // {
// // 	int		i;
// // 	t_table	*eye;

// // 	eye = (t_table *)pp;
// // 	while (1)
// // 	{
// // 		i = 0;
// // 		while (i < eye->head)
// // 		{
// // 			pthread_mutex_lock(&eye->death);
// // 			// 1. Check for starvation (philosopher dies when it should)
// // 			if ((get_time_ms()
					//- eye->philop[i].last_time_eat) > (size_t)eye->die_time)
// // 			{
// // 				eye->someone_died = true;
// // 				o_print(&eye->philop[i], 5, i + 1);
// // 				pthread_mutex_unlock(&eye->death);
// // 				return (NULL); // Ends program when someone died
// // 			}
// // 			pthread_mutex_unlock(&eye->death);
// // 			i++;
// // 		}

// // 		// 2. Check for global termination condition (everyone is full)
// // 		if (we_r_full(eye) == 0)
// // 		{
// // 			pthread_mutex_lock(&eye->death);
// // 			eye->someone_died = true;
				// Set flag to stop running philosopher threads
// // 			o_print(&eye->philop[0], 6, 1); // Print 'Everyone is full'
// // 			pthread_mutex_unlock(&eye->death);
// // 			return (NULL); // Ends program when everyone is full
// // 		}

// // 		// 3. Early exit if a philosopher thread set the death flag
// // 		pthread_mutex_lock(&eye->death);
// // 		if (eye->someone_died)
// // 		{
// // 			pthread_mutex_unlock(&eye->death);
// // 			return (NULL);
// // 		}
// // 		pthread_mutex_unlock(&eye->death);

// // 		usleep(100); // Wait for a short duration
// // 	}
// // }
// //this is gemini:

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

//            
				// Print the success message and return (// 			return (o_print(&eye->philop[0],
					//	6, 1), NULL));
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

// // void	*dead_yet(void *pp)
// // {
// // 	int		id;
// // 	t_table	*eye;

// // 	eye = (t_table *)pp;
// // 	while (1)
// // 	{
// // 		id = 0;
// // 		while (id < eye->head && eye->someone_died != true)
// // 		{
// // 			pthread_mutex_lock(&eye->death);
// // 			// if (eye->someone_died)
// // 			// {
// // 			// 	pthread_mutex_unlock(&eye->death);
// // 			// 	return (NULL);
// // 			// }
// // 			if (we_r_full(eye) == 0)
// // 			{
// // 				eye->someone_died = true;
// // 				o_print(&eye->philop[0], 6, 1);
// // 				pthread_mutex_unlock(&eye->death);
// // 				return (NULL);
// // 			}
// // 			if (eat_gap(eye, id) >= (size_t)eye->die_time)
// // 			{
// // 				eye->someone_died = true;
// // 				o_print(&eye->philop[id], 5, id + 1);
// // 				pthread_mutex_unlock(&eye->death);
// // 				return (NULL);
// // 			}
// // 			pthread_mutex_unlock(&eye->death);
// // 			id++;
// // 		}
// // 		usleep(500);
// // 	}
// // 	return (NULL);
// // }

// int	we_r_full(t_table *pp)
// {
// 	int	id;

// 	id = 0;
// 	if (pp->min_times_to_eat <= -1)
// 		return (1);
// 	while (id < pp->head)
// 	{
// 		pthread_mutex_lock(&pp->death);
// 		if (pp->philop[id].full == 0)
// 			return (pthread_mutex_unlock(&pp->death), 1);
// 			// return (pthread_mutex_unlock(&pp->death), 1);
// 		pthread_mutex_unlock(&pp->death);
// 		id++;
// 	}
// 	//pthread_mutex_unlock(&pp->death);
// 	return (0);
// }

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
	if (death(philop) == 1)
		return (NULL);
	while (1)
	{
		if (death(philop) == 1)
			break ;
		if (philop->full == 1)
			return (NULL);
		eat(philop);
		if (death(philop) == 1)
			break ;
		p_sleep(philop);
		if (death(philop) == 1)
			break ;
		thinking(philop);
		if (death(philop) == 1)
			break ;
	}
	return (NULL);
}

int	death(t_philop *pp)
{
	pthread_mutex_lock(&pp->table->death);
	if (pp->table->someone_died == true)
	{
		pthread_mutex_unlock(&pp->table->death);
		return (1);
	}
	pthread_mutex_unlock(&pp->table->death);
	return (0);
}
// have to set checking_dead in the routine. so philops exit in time
void	*dead_yet(void *pp)
{
	t_table	*eye;

	eye = (t_table *)pp;
	while (1)
	{
		if (we_r_full(eye) == 0)
			return (o_print(&eye->philop[0], 6, 1), NULL);
		if (check_starved(eye) == 1)
			return (NULL);
		usleep(500);
	}
	return (NULL);
}

int	check_starved(t_table *pp)
{
	int	id;

	id = 0;
	while (id < pp->head)
	{
		if (eat_gap(pp, id) >= (size_t)pp->die_time)
		{
			pthread_mutex_lock(&pp->death);
			pp->someone_died = true;
			pthread_mutex_unlock(&pp->death);
			o_print(&pp->philop[id], 5, id + 1);
			return (1);
		}
		id++;
	}
	return (0);
}

int	we_r_full(t_table *pp)
{
	int id;

	// pthread_mutex_lock(&pp->death);
	id = 0;
	if (pp->min_times_to_eat <= -1)
		return (1);
	while (id < pp->head)
	{
		if (pp->philop[id].full == 0)
			return (1);
		// return (pthread_mutex_unlock(&pp->death), 1);
		id++;
	}
	// pthread_mutex_unlock(&pp->death);
	return (0);
}
