/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:59:43 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/23 18:59:56 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table *table)
{
	int	i;

	if (table->forks)
	{
		i = -1;
		while (++i < table->num_philos)
			pthread_mutex_destroy(&table->forks[i]);
		free(table->forks);
	}
	if (table->philos)
	{
		i = -1;
		while (++i < table->num_philos)
			pthread_join(table->philos[i].thread, NULL);
		free(table->philos);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->eat_mutex);
	free(table);
}
