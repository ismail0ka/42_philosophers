/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:32:12 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/27 18:41:20 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sync_print(t_philo *philo, const char *message)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld Philo %d %s", get_time() - philo->table->start_time, philo->id, message);
	pthread_mutex_unlock(&philo->table->print_mutex);
}
