/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_philos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:31:56 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/28 17:19:03 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	a_philo_died(t_table *table)
{
	int i;

    i = -1;
    while (++i < table->num_philos)
    {
		pthread_mutex_lock(&table->state_mutex);
		if (get_time() - table->philos[i].last_meal_time > table->time_to_die)
        {
            table->death_flag = 1;
            sync_print(&table->philos[i], "has died\n");
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
		return (1);
	i = -1;
	while (++i < table->num_philos)
	{
		if (table->philos[i].eat_count < table->must_eat_count)
			return (0);
	}
	return (1);
}

void	*monitor_philos(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (!(a_philo_died(table) || all_philos_ate(table)))
	{}
	return (NULL);
}