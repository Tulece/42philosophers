/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:49 by anporced          #+#    #+#             */
/*   Updated: 2024/07/08 21:45:15 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	get_state_color(t_state state, const char **state_color)
{
	static const char	*state_colors[] = {
		BLUE,
		YELLOW,
		GREEN,
		CYAN,
		RED
	};

	*state_color = state_colors[state];
}

void	get_status_message(t_state state, const char **status_message)
{
	static const char	*status[] = {
		"is thinking",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"died"
	};

	*status_message = status[state];
}

void	print_philosopher_status(t_philosopher *philo, t_state state)
{
	const char	*state_color;
	const char	*status_message;
	long		timestamp;

	pthread_mutex_lock(&philo->params->stop_mutex);
	if (philo->params->stop)
	{
		pthread_mutex_unlock(&philo->params->stop_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->params->stop_mutex);
	timestamp = get_timestamp() - philo->params->start_time;
	get_state_color(state, &state_color);
	get_status_message(state, &status_message);
	pthread_mutex_lock(&philo->params->print_mutex);
	pthread_mutex_lock(&philo->params->stop_mutex);
	if (!philo->params->stop)
		printf("%s%ld %d %s%s\n", state_color, timestamp, philo->id, \
status_message, RESET);
	pthread_mutex_unlock(&philo->params->stop_mutex);
	pthread_mutex_unlock(&philo->params->print_mutex);
}
