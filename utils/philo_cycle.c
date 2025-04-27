/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:45 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/27 18:14:57 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_table *table)
{
	pthread_mutex_lock(&table->death_mutex);
	if (table->death_flag)
		return (pthread_mutex_unlock(&table->death_mutex), 1);
	pthread_mutex_unlock(&table->death_mutex);
	return (0);
}

void	eaty_sleepy_thinky(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->table->print_mutex);
	printf("%lld Philo %d has taken a fork\n", get_time() - philo->table->start_time, philo->id);
	printf("%lld Philo %d is eating\n", get_time() - philo->table->start_time, philo->id);
	pthread_mutex_lock(&philo->table->eat_mutex);
	philo->last_meal_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->eat_mutex);
	usleep(philo->table->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
	printf("%lld Philo %d is sleeping\n", get_time() - philo->table->start_time, philo->id);
	usleep(philo->table->time_to_sleep * 1000);
	printf("%lld Philo %d is thinking\n", get_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(10);
	while (!philo_died(table))
		eaty_sleepy_thinky(philo);
	return (NULL);
}
