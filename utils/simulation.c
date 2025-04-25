/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:49:52 by ikarouat          #+#    #+#             */
/*   Updated: 2025/04/25 15:19:38 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (!philo->someone_died)
	{
		if (table->num_philos == 1)
		{
			pthread_mutex_lock(&table->forks[0]);
			usleep(table->time_to_die * 1000);
			pthread_mutex_unlock(&table->forks[0]);
			return (NULL);
		}
		if (philo->id % 2 == 0)
		{
		    pthread_mutex_lock(&table->forks[philo->right_fork]);
		    pthread_mutex_lock(&table->forks[philo->left_fork]);
		}
		else
		{
		    pthread_mutex_lock(&table->forks[philo->left_fork]);
		    pthread_mutex_lock(&table->forks[philo->right_fork]);
		}
		pthread_mutex_lock(&table->print_mutex);
		printf("Philosopher %d is eating\n", philo->id);
		pthread_mutex_unlock(&table->print_mutex);
		
		usleep(table->time_to_eat * 1000);
		philo->last_meal_time = get_time();
		philo->eat_count++;
		if (philo->eat_count == table->must_eat_count)
		{
			pthread_mutex_unlock(&table->forks[philo->left_fork]);
			pthread_mutex_unlock(&table->forks[philo->right_fork]);
			return (NULL);
		}
		pthread_mutex_unlock(&table->forks[philo->left_fork]);
		pthread_mutex_unlock(&table->forks[philo->right_fork]);
		
		pthread_mutex_lock(&table->print_mutex);
		printf("Philosopher %d is sleeping\n", philo->id);
		pthread_mutex_unlock(&table->print_mutex);
		usleep(table->time_to_sleep * 1000);
		
		pthread_mutex_lock(&table->print_mutex);
		printf("Philosopher %d is thinking\n", philo->id);
		pthread_mutex_unlock(&table->print_mutex);
	}
	return (NULL);
}

void	propagate_death(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->table->num_philos)
	{
		pthread_mutex_lock(&philos[i].table->eat_mutex);
		philos[i].someone_died = 1;
		pthread_mutex_unlock(&philos[i].table->eat_mutex);
	}
}

void	monitor_philos(t_table *table)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < table->num_philos)
		{
			if (get_time() - table->philos[i].last_meal_time > table->time_to_die)
			{
				pthread_mutex_lock(&table->print_mutex);
				printf("Philosopher %d has died\n", table->philos[i].id);
				propagate_death(table->philos);
				pthread_mutex_unlock(&table->print_mutex);
				return ;
			}
		}
		usleep(1000);
	}
}

void	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philos)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &philo_routine,
				&table->philos[i]) != 0)
		{
			write(2, "Error: Failed to create philosopher thread\n", 43);
			return ;
		}
	}
	monitor_philos(table);
	i = -1;
	while (++i < table->num_philos)
		pthread_join(table->philos[i].thread, NULL);
}
