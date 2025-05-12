/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikarouat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:01:27 by ikarouat          #+#    #+#             */
/*   Updated: 2025/05/12 14:39:42 by ikarouat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, const char **argv)
{
	t_table	*table;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo <number_of_philos> <time_to_die>\
 <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]\n");
		return (1);
	}
	table = malloc(sizeof(t_table));
	if (!table)
		return (1);
	if (!init_table(table, argc, argv))
	{
		write(2, "Error: Failed to initialize table\n", 35);
		return (free(table), 1);
	}
	if (!init_philos(table))
	{
		write(2, "Error: Failed to initialize philosophers\n", 40);
		return (free(table), 1);
	}
	if (table->must_eat_count == 0 || table->num_philos == 0)
		free_table(table);
	start_simulation(table);
	return (0);
}
