/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:31:56 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/08 18:54:06 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	a_philo_died(t_table *table)
{
	int			i;
	long long	time_since_last_meal;
	long long	current_time;

	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->state_mutex);
		time_since_last_meal = get_time() - table->philos[i].last_meal_time;
		if (time_since_last_meal > table->time_to_die)
		{
			table->death_flag = 1;
			current_time = get_time() - table->start_time;
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld %d has died\n", current_time, table->philos[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			pthread_mutex_unlock(&table->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(&table->state_mutex);
	}
	return (0);
}

int	all_philos_ate(t_table *table)
{
	int	i;

	if (table->must_eat_count == -1)
		return (0);
	i = -1;
	while (++i < table->num_philos)
	{
		pthread_mutex_lock(&table->state_mutex);
		if (table->philos[i].eat_count < table->must_eat_count)
			return (pthread_mutex_unlock(&table->state_mutex), 0);
		pthread_mutex_unlock(&table->state_mutex);
	}
	return (1);
}

void	*monitor_philos(t_table *table)
{
	while (1)
	{
		if (a_philo_died(table) || all_philos_ate(table))
			break ;
		usleep(100);
	}
	return (NULL);
}
