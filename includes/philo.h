/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tulece <tulece@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 17:10:06 by anporced          #+#    #+#             */
/*   Updated: 2024/07/07 21:19:02 by tulece           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"

typedef enum e_state
{
	THINKING,
	TAKING_FORK,
	EATING,
	SLEEPING,
	DEAD
}	t_state;

typedef struct s_philosopher
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_params	*params;
}					t_philosopher;

typedef struct s_params
{
	int				num_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long			start_time;
	int				max_meals;
	int				stop;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	stop_mutex;
	t_philosopher	*philosophers;
}					t_params;

// Initialization
int		init_params(t_params *params, int argc, char **argv);
int		init_mutexes(t_params *params);
int		init_forks(t_params *params);
int		init_philosophers(t_params *params);

// Utility
long	get_timestamp(void);
void	custom_usleep(int milliseconds);
int		parse_arguments(int argc, char **argv, t_params *params);
void	handle_error(const char *msg);
int		parse_int(const char *s);

// Routines
void	*philosopher_routine(void *arg);
void	*monitor_routine(void *arg);
void	print_philosopher_status(t_philosopher *philo, t_state state);

// Cleanup
void	cleanup(t_params *params);

#endif
