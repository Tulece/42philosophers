/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:55 by anporced          #+#    #+#             */
/*   Updated: 2024/07/06 17:09:58 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	take_forks(t_philosopher *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, TAKING_FORK);
	if (philo->left_fork == philo->right_fork)
	{
		custom_usleep(philo->params->time_to_die);
		print_status(philo, DEAD);
		pthread_mutex_lock(&philo->params->stop_mutex);
		philo->params->stop = 1;
		pthread_mutex_unlock(&philo->params->stop_mutex);
		pthread_mutex_unlock(philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, TAKING_FORK);
	}
}

void	eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	philo->last_meal = get_timestamp();
	print_status(philo, EATING);
	pthread_mutex_unlock(&philo->params->death_mutex);
	custom_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(&philo->params->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->params->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
