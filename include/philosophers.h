/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:16:39 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 18:06:00 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "datastructures.h"

# define DEATH_MESSAGE "died"
# define TAKENFORK_MESSAGE "has taken a fork"
# define EATING_MESSAGE "is eating"
# define SLEEPING_MESSAGE "is sleeping"
# define THINKING_MESSAGE "is thinking"

enum e_singleton_action {
	SINGLETON_GET_VALUE,
	SINGLETON_INIT,
	SINGLETON_DESTROY,
	SINGLETON_A,
	SINGLETON_B,
	SINGLETON_MAX
};

int32_t	create_philosophers(t_philo_setup *init_data);
void	*philosopher_routine(void *arg);
void	*observer_routine(void *arg);

int32_t	eating(t_philo *const philosopher);
int32_t	thinking(t_philo *const philosopher);
int32_t	sleeping(t_philo *const philosopher);
int32_t	death(t_philo *const philosopher);

bool	check_philo_state(t_philo *const philosopher);

void	queue_msg_event(
			t_philo *const philosopher,
			enum e_philosopher_state action);

#endif
