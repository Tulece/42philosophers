/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:52 by anporced          #+#    #+#             */
/*   Updated: 2024/07/06 21:56:34 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philosopher *philo, t_state state)
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
		printf("%ld %d %s\n",
			timestamp, philo->id, status[state]);
	pthread_mutex_unlock(&philo->params->print_mutex);
}
