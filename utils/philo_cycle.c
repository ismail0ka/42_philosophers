/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:45 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/27 18:39:25 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eaty_sleepy_thinky(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	sync_print(philo, "has taken a fork\n");
	sync_print(philo, "is eating\n");
	pthread_mutex_lock(&philo->table->eat_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->eat_mutex);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	sync_print(philo, "is sleeping\n");
	usleep(philo->table->time_to_sleep * 1000);
	sync_print(philo, "is thinking\n");
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(10);
	while (1)
		eaty_sleepy_thinky(philo);
	return (NULL);
}
