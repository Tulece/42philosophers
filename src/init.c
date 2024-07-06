/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:06:28 by anporced          #+#    #+#             */
/*   Updated: 2024/07/06 17:30:31 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_mutexes(t_params *params)
{
	if (pthread_mutex_init(&params->print_mutex, NULL) != 0
		|| pthread_mutex_init(&params->death_mutex, NULL) != 0
		|| pthread_mutex_init(&params->meal_mutex, NULL) != 0
		|| pthread_mutex_init(&params->stop_mutex, NULL) != 0)
	{
		handle_error("Failed to initialize mutex");
		return (0);
	}
	return (1);
}

int	init_forks(t_params *params)
{
	int	i;

	params->forks = malloc(params->num_philosophers * sizeof(pthread_mutex_t));
	if (!params->forks)
	{
		handle_error("Failed to allocate memory for forks");
		return (0);
	}
	i = 0;
	while (i < params->num_philosophers)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			handle_error("Failed to initialize fork mutex");
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philosopher(t_philosopher *philo, int id, t_params *params)
{
	philo->id = id + 1;
	philo->left_fork = &params->forks[id];
	philo->right_fork = &params->forks[(id + 1) % params->num_philosophers];
	philo->last_meal = get_timestamp();
	philo->meals_eaten = 0;
	philo->params = params;
	if (pthread_create(&philo->thread, NULL, philosopher_routine, philo) != 0)
	{
		handle_error("Failed to create philosopher thread");
		return (0);
	}
	return (1);
}

int	init_philosophers(t_params *params)
{
	int	i;

	params->philosophers = malloc(params->num_philosophers \
	* sizeof(t_philosopher));
	if (!params->philosophers)
	{
		handle_error("Failed to allocate memory for philosophers");
		return (0);
	}
	i = 0;
	while (i < params->num_philosophers)
	{
		if (!init_philosopher(&params->philosophers[i], i, params))
			return (0);
		i++;
	}
	return (1);
}

int	init_params(t_params *params, int argc, char **argv)
{
	if (!parse_arguments(argc, argv, params))
		return (0);
	if (!init_forks(params) || !init_mutexes(params) \
	|| !init_philosophers(params))
		return (0);
	return (1);
}
