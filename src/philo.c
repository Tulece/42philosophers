/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:49 by anporced          #+#    #+#             */
/*   Updated: 2024/07/07 09:31:51 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_philosopher_status(t_philosopher *philo, t_state state)
{
	static const char	*status[] = {
		"is thinking",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"died"
	};
	long				timestamp;

	pthread_mutex_lock(&philo->params->stop_mutex);
	if (philo->params->stop)
	{
		pthread_mutex_unlock(&philo->params->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->params->stop_mutex);
	timestamp = get_timestamp();
	pthread_mutex_lock(&philo->params->print_mutex);
	if (!philo->params->stop)
		printf("%ld %d %s\n", timestamp, philo->id, status[state]);
	pthread_mutex_unlock(&philo->params->print_mutex);
}

void philosopher_take_forks(t_philosopher *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->params->num_philosophers == 1)
	{
		print_philosopher_status(philo, THINKING);
		custom_usleep(philo->params->time_to_die);
		print_philosopher_status(philo, DEAD);
		pthread_mutex_lock(&philo->params->stop_mutex);
		philo->params->stop = 1;
		pthread_mutex_unlock(&philo->params->stop_mutex);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	else
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	pthread_mutex_lock(first_fork);
	print_philosopher_status(philo, TAKING_FORK);
	pthread_mutex_lock(second_fork);
	print_philosopher_status(philo, TAKING_FORK);
}


void	philosopher_eat(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->params->death_mutex);
	philo->last_meal = get_timestamp();
	print_philosopher_status(philo, EATING);
	pthread_mutex_unlock(&philo->params->death_mutex);
	custom_usleep(philo->params->time_to_eat);
	pthread_mutex_lock(&philo->params->meal_mutex);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->params->meal_mutex);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*philo;
	int				should_stop;

	philo = (t_philosopher *)arg;
	should_stop = philo->params->stop;
	while (!should_stop)
	{
		print_philosopher_status(philo, THINKING);
		philosopher_take_forks(philo);
		if (philo->left_fork == philo->right_fork)
			break ;
		philosopher_eat(philo);
		print_philosopher_status(philo, SLEEPING);
		custom_usleep(philo->params->time_to_sleep);
		pthread_mutex_lock(&philo->params->stop_mutex);
		should_stop = philo->params->stop;
		pthread_mutex_unlock(&philo->params->stop_mutex);
	}
	return (NULL);
}
