/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:49:52 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/27 18:35:26 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_simulation(t_table *table) {
    int i;
    pthread_t monitor;

    if (pthread_create(&monitor, NULL, &monitor_philos, table) != 0) {
        write(2, "Error: Failed to create monitor thread\n", 39);
        return;
    }
    i = -1;
    while (++i < table->num_philos) {
        if (pthread_create(&table->philos[i].thread, NULL, &philo_cycle, &table->philos[i]) != 0) {
            write(2, "Error: Failed to create philosopher thread\n", 43);
            return;
        }
    }
    i = -1;
    while (++i < table->num_philos) {
        pthread_join(table->philos[i].thread, NULL);
    }
    if (pthread_join(monitor, NULL) != 0) {
        write(2, "Error: Failed to join monitor thread\n", 37);
    }
}

/*void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, &monitor_philos, table) != 0)
	{
		write(2, "Error: Failed to create monitor thread\n", 39);
		return ;
	}
	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_cycle,
			&table->philos[i]) != 0)
			return ;
	}
	if (pthread_join(monitor, NULL) != 0)
	{
		write(2, "Error: Failed to join monitor thread\n", 37);
		return ;
	}
	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread, NULL);
}*/
