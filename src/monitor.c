/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulece <tulece@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:44 by anporced          #+#    #+#             */
/*   Updated: 2024/07/07 13:39:37 by tulece           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	monitor_philosopher(t_params *params, int i)
{
	pthread_mutex_lock(&params->death_mutex);
	if ((get_timestamp() - params->philosophers[i].last_meal) \
		> params->time_to_die)
	{
		print_philosopher_status(&params->philosophers[i], DEAD);
		pthread_mutex_lock(&params->stop_mutex);
		params->stop = 1;
		pthread_mutex_unlock(&params->stop_mutex);
	}
	pthread_mutex_unlock(&params->death_mutex);
}

int	monitor_meals(t_params *params)
{
	int	all_philosophers_done;
	int	i;

	all_philosophers_done = 1;
	i = 0;
	while (i < params->num_philosophers)
	{
		monitor_philosopher(params, i);
		if (params->max_meals > 0)
		{
			pthread_mutex_lock(&params->meal_mutex);
			if (params->philosophers[i].meals_eaten < params->max_meals)
				all_philosophers_done = 0;
			pthread_mutex_unlock(&params->meal_mutex);
		}
		else
			all_philosophers_done = 0;
		if (params->stop)
			break ;
		i++;
	}
	return (all_philosophers_done);
}

void	check_meals(t_params *params)
{
	pthread_mutex_lock(&params->print_mutex);
	printf("All philosophers have eaten at least %d times.\n", \
params->max_meals);
	pthread_mutex_lock(&params->stop_mutex);
	params->stop = 1;
	pthread_mutex_unlock(&params->stop_mutex);
	pthread_mutex_unlock(&params->print_mutex);
}

void	*monitor_routine(void *arg)
{
	t_params	*params;
	int			should_stop;

	params = (t_params *)arg;
	should_stop = params->stop;
	while (!should_stop)
	{
		if (monitor_meals(params))
		{
			check_meals(params);
		}
		pthread_mutex_lock(&params->stop_mutex);
		should_stop = params->stop;
		pthread_mutex_unlock(&params->stop_mutex);
		custom_usleep(100);
	}
	return (NULL);
}
