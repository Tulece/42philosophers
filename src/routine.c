/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 21:31:40 by anporced          #+#    #+#             */
/*   Updated: 2024/07/08 21:32:09 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	select_forks(t_philosopher *philo, pthread_mutex_t **first_fork,
pthread_mutex_t **second_fork)
{
	if (philo->params->num_philosophers == 1)
	{
		print_philosopher_status(philo, TAKING_FORK);
		custom_usleep(philo->params->time_to_die);
		print_philosopher_status(philo, DEAD);
		pthread_mutex_lock(&philo->params->stop_mutex);
		philo->params->stop = 1;
		pthread_mutex_unlock(&philo->params->stop_mutex);
		*first_fork = NULL;
		*second_fork = NULL;
		return ;
	}
	if (philo->id % 2 == 0)
	{
		*first_fork = philo->right_fork;
		*second_fork = philo->left_fork;
	}
	else
	{
		*first_fork = philo->left_fork;
		*second_fork = philo->right_fork;
	}
}

void	philosopher_take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	select_forks(philo, &first_fork, &second_fork);
	if (first_fork && second_fork)
	{
		pthread_mutex_lock(first_fork);
		print_philosopher_status(philo, TAKING_FORK);
		pthread_mutex_lock(second_fork);
		print_philosopher_status(philo, TAKING_FORK);
	}
}

void	philosopher_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	pthread_mutex_lock(&philo->params->meal_mutex);
	philo->last_meal = get_timestamp();
	print_philosopher_status(philo, EATING);
	pthread_mutex_unlock(&philo->params->death_mutex);
	pthread_mutex_unlock(&philo->params->meal_mutex);
	custom_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(&philo->params->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->params->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	philosopher_sleep(t_philosopher *philo)
{
	print_philosopher_status(philo, SLEEPING);
	custom_usleep(philo->params->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				should_stop;

	philo = (t_philosopher *)arg;
	should_stop = 0;
	while (!should_stop)
	{
		philosopher_take_forks(philo);
		if (philo->left_fork == philo->right_fork)
			break ;
		philosopher_eat(philo);
		philosopher_sleep(philo);
		print_philosopher_status(philo, THINKING);
		pthread_mutex_lock(&philo->params->stop_mutex);
		should_stop = philo->params->stop;
		pthread_mutex_unlock(&philo->params->stop_mutex);
	}
	return (NULL);
}
