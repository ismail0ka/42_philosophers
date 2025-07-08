/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:32:12 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/03 14:56:03 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_print(t_philo *philo, const char *message)
{
	long long	current_time;

	pthread_mutex_lock(&philo->table->state_mutex);
	if (philo->table->death_flag)
	{
		pthread_mutex_unlock(&philo->table->state_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->table->print_mutex);
	current_time = get_time() - philo->table->start_time;
	printf("%lld %d %s", current_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
	pthread_mutex_unlock(&philo->table->state_mutex);
}
