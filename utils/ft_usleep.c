/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:00:57 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/06 21:43:11 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(unsigned long long duration_ms, t_table *table)
{
	unsigned long long	start_ms;
	unsigned long long	current_ms;
	unsigned long long	elapsed_ms;

	start_ms = get_time();
	while (1)
	{
		current_ms = get_time();
		elapsed_ms = current_ms - start_ms;
		pthread_mutex_lock(&table->state_mutex);
		if (elapsed_ms >= duration_ms || table->death_flag)
		{
			pthread_mutex_unlock(&table->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&table->state_mutex);
		usleep(100);
	}
}
