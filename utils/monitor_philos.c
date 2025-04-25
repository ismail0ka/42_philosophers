/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:31:56 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/25 19:29:50 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_alive(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->death_mutex);
		if (get_time() - table->philos[i].last_meal_time > table->time_to_die)
		{
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld Philo %d died\n", get_time() - table->start_time, table->philos[i].id + 1);
			pthread_mutex_unlock(&table->print_mutex);
			table->death_flag = 1;
			pthread_mutex_unlock(&table->death_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->death_mutex);
		usleep(100);	
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