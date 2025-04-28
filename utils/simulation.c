/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:49:52 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/28 15:11:41 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_table *table)
{
	sync_print(&table->philos[0], "has taken a fork\n");
	usleep(table->time_to_die * 1000);
	sync_print(&table->philos[0], "has died\n");
}

void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_philos, table) != 0)
	{
		write(2, "Error: Failed to create monitor thread\n", 39);
		return ;
	}
	if (table->num_philos == 1)
	{
		one_philo(table);
		return ;
	}
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_cycle,
			&table->philos[i]) != 0)
			return ;
	}
	i = -1;
	if (pthread_join(monitor, NULL) != 0)
	{
		write(2, "Error: Failed to join monitor thread\n", 37);
		return ;
	}
	return ;
}
