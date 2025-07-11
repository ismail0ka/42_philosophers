/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:05:02 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/06 21:44:09 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				eat_count;
	long long		last_meal_time;
	pthread_t		thread;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				num_philos;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat_count;
	int				death_flag;
	int				must_eat_flag;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	print_mutex;
}	t_table;

//Init
int			init_table(t_table *table, int argc, const char **argv);
int			init_philos(t_table *table);
//Simulation
void		*monitor_philos(t_table *table);
void		*philo_cycle(void *arg);
void		start_simulation(t_table *table);
//Utils
void		sync_print(t_philo *philo, const char *message);
int			ft_atoi(const char *str);
long long	get_time(void);
void		ft_usleep(unsigned long long duration_ms, t_table *table);
//Cleanup
void		cleanup(t_table *table);

#endif //PHILO_H
