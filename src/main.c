/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulece <tulece@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:41 by anporced          #+#    #+#             */
/*   Updated: 2024/07/07 22:07:19 by tulece           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_params	params;
	pthread_t	monitor_thread;

	if (!init_params(&params, argc, argv))
		return (EXIT_FAILURE);
	if (pthread_create(&monitor_thread, NULL, monitor_routine, &params) != 0)
	{
		handle_error("Failed to create monitor thread");
		cleanup(&params);
		return (EXIT_FAILURE);
	}
	pthread_join(monitor_thread, NULL);
	cleanup(&params);
	return (EXIT_SUCCESS);
}
