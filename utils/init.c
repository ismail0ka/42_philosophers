/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:04:21 by ikarouat          #+#    #+#             */
/*   Updated: 2025/05/13 16:29:44 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_pos_number(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	valid_args(int argc, const char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!is_pos_number(argv[i]))
		{
			printf("Error: Invalid argument '%s'\n", argv[i]);
			return (0);
		}
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
	}
	if (pthread_mutex_init(&table->state_mutex, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->print_mutex, NULL) != 0)
		return (0);
	return (1);
}

int	init_table(t_table *table, int argc, const char **argv)
{
	if (!valid_args(argc, argv))
		return (0);
	table->num_philos = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat_count = ft_atoi(argv[5]);
	else
		table->must_eat_count = -1;
	table->start_time = get_time();
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (0);
	if (!init_forks(table))
		return (free(table->forks), 0);
	table->philos = NULL;
	table->death_flag = 0;
	table->must_eat_flag = 0;
	return (1);
}

int	init_philos(t_table *table)
{
	int	i;

	table->philos = malloc(sizeof(t_philo) * table->num_philos);
	if (!table->philos)
		return (0);
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].last_meal_time = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = i;
		table->philos[i].right_fork = (i + 1) % table->num_philos;
	}
	return (1);
}
