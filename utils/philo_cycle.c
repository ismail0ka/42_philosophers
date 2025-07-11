/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <ikarouat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:54:45 by ikarouat          #+#    #+#             */
/*   Updated: 2025/07/11 23:00:19 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		sync_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		sync_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right_fork]);
		sync_print(philo, "has taken a fork\n");
		pthread_mutex_lock(&philo->table->forks[philo->left_fork]);
		sync_print(philo, "has taken a fork\n");
	}
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->table->state_mutex);
	sync_print(philo, "is eating\n");
	ft_usleep(philo->table->time_to_eat, philo->table);
	pthread_mutex_lock(&philo->table->state_mutex);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->table->state_mutex);
	pthread_mutex_unlock(&philo->table->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->table->forks[philo->right_fork]);
}

void	sleep_and_think(t_philo *philo)
{
	sync_print(philo, "is sleeping\n");
	ft_usleep(philo->table->time_to_sleep, philo->table);
	sync_print(philo, "is thinking\n");
	usleep(200);
}

void	*philo_cycle(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->table->state_mutex);
		if (philo->table->death_flag || (philo->table->must_eat_count != -1
				&& (philo->eat_count >= philo->table->must_eat_count
					|| philo->table->must_eat_flag)))
		{
			pthread_mutex_unlock(&philo->table->state_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->table->state_mutex);
		eat(philo);
		sleep_and_think(philo);
	}
	return (NULL);
}
