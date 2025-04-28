/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:31:56 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/28 15:13:09 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (get_time() - table->philos[i].last_meal_time
			> table->time_to_die)
		{
			table->philos[i].died = 1;
			pthread_mutex_unlock(&table->state_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
	return (1);
}

void	find_dead_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->philos[i].died)
		{
			sync_print(&table->philos[i], "has died\n");
			pthread_mutex_unlock(&table->state_mutex);
			return ;
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
}

void	*monitor_philos(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (!check_death(table))
			break ;
	}
	find_dead_philo(table);
	return (NULL);
}