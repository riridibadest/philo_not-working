/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuerliu <yuerliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 16:27:01 by yuerliu           #+#    #+#             */
/*   Updated: 2025/10/22 20:30:53 by yuerliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philop
{
	int				id;
	int				eat_count;
	int				fork;
	int				full;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	size_t			last_time_eat;
	struct s_table	*table;
}					t_philop;

// for garbage collection
typedef struct s_list
{
	void			*now;
	struct s_list	*front;
}					t_list;

typedef struct s_table
{
	int				head;
	size_t			start_time;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				min_times_to_eat;
	bool			someone_died;
	t_list			*garbabe_location;
	pthread_mutex_t	death;
	pthread_mutex_t	*forks;
	pthread_mutex_t	p_lock;
	t_philop		*philop;
}					t_table;

// philo actions
int					eat(t_philop *pp);
void				p_sleep(t_philop *pp);
void				thinking(t_philop *pp);
void				solo_eating(t_philop *pp);
void				*life_of_philop(void *pp);
// Initialization
t_table				read_input(int ac, char **av);
void				init_philop(t_table *pimp);
void				make_philops(t_table *pp);
t_table				make_table(int ac, char **av);
// SIMULATION
void				feast_time(t_table *pp);
void				*dead_yet(void *pp);
int					we_r_full(t_table *pp);
// SIMULATION HELPERS
size_t				eat_gap(t_table *pp, int id);
void				take_forks(t_philop *pp, size_t id);
void				smart_rest(t_philop *pp, size_t i);
size_t				get_time_ms(void);
void				o_print(t_philop *pp, int i, int id);
int					death_check(t_table *pp);
int death(t_philop *pp);
void				destroy_mutexes(t_table *table);
int check_starved(t_table *pp);

// GARABAGE COLLECTION
void				clean_up(t_list *garbabe);
void				*malloc_table_sth(t_table *pp, size_t size);
// input helper
int					ok_input(int ac, char **av);
int					ft_isdigit(int num);
int					zero(int ac, char **av);
int					ft_atoi(const char *str);

#endif