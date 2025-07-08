/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 21:51:22 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/06 21:51:24 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_table *table)
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
		free(table->philos);
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->state_mutex);
	free(table);
}
