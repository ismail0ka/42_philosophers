/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:49:52 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/06 21:43:53 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	one_philo(t_table *table)
{
	sync_print(&table->philos[0], "has taken a fork\n");
	ft_usleep(table->time_to_die, table);
	sync_print(&table->philos[0], "has died\n");
}

void	start_simulation(t_table *table)
{
	int					i;
	pthread_t			monitor;
	unsigned long long	start_time;

	if (table->num_philos == 1)
	{
		one_philo(table);
		return ;
	}
	start_time = get_time();
	i = -1;
	while (++i < table->num_philos)
	{
		table->philos[i].last_meal_time = start_time;
		if (pthread_create(&table->philos[i].thread, NULL,
				&philo_cycle, &table->philos[i]) != 0)
			return ;
	}
	if (pthread_create(&monitor, NULL, (void *)monitor_philos, table) != 0)
		return ;
	pthread_join(monitor, NULL);
	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread, NULL);
}
