/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anporced <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:09:46 by anporced          #+#    #+#             */
/*   Updated: 2024/07/06 17:23:12 by anporced         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_arguments(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philos time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philos_must_eat]\n",
			argv[0]);
		return (0);
	}
	params->num_philosophers = parse_int(argv[1]);
	params->time_to_die = parse_int(argv[2]);
	params->time_to_eat = parse_int(argv[3]);
	params->time_to_sleep = parse_int(argv[4]);
	if (argc == 6)
		params->max_meals = parse_int(argv[5]);
	else
		params->max_meals = -1;
	params->stop = 0;
	return (1);
}

int	parse_int(const char *s)
{
	int	res;

	res = 0;
	while (*s == ' ' || *s == '\n' || *s == '\t' \
		|| *s == '\r' || *s == '+' || *s == '-')
		s++;
	while ('0' <= *s && *s <= '9')
		res = res * 10 + (*s++ - '0');
	return (res);
}
