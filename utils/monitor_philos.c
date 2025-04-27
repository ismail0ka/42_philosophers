/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:31:56 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/27 18:40:41 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->eat_mutex);
	if (get_time() - philo->last_meal_time > philo->table->time_to_die)
	{
		pthread_mutex_unlock(&philo->table->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->eat_mutex);
	return (0);
}

int	check_all_alive(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (philo_died(&table->philos[i]))
		{
			sync_print(&table->philos[i], "died\n");
			pthread_mutex_lock(&table->death_mutex);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (0);
		}
	}
	return (1);
}

void	*monitor_philos(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (!check_all_alive(table))
			break ;
	}
	return (NULL);
}