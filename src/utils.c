/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <anporced@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:10:02 by anporced          #+#    #+#             */
/*   Updated: 2024/07/09 14:38:56 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (str[i]);
}

void	handle_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
}

void	cleanup(t_params *params)
{
	int	i;

	i = 0;
	while (i < params->num_philosophers)
	{
		pthread_join(params->philosophers[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&params->print_mutex);
	pthread_mutex_destroy(&params->death_mutex);
	pthread_mutex_destroy(&params->meal_mutex);
	pthread_mutex_destroy(&params->stop_mutex);
	free(params->forks);
	free(params->philosophers);
}
