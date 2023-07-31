/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   simulation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/01 12:15:24 by vincent       #+#    #+#                 */
/*   Updated: 2022/08/15 15:23:56 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "datastructures.h"
#include "helpers.h"
#include "philo_time.h"
#include "writer.h"

void	*philosopher_routine(void *arg)
{
	t_philo *const	philosopher = arg;
	int64_t			now;

	pthread_mutex_lock(philosopher->setup->global_event);
	if (philosopher->setup->terminate == true)
	{
		pthread_mutex_unlock(philosopher->setup->global_event);
		return (arg);
	}
	pthread_mutex_unlock(philosopher->setup->global_event);
	pthread_mutex_lock(&philosopher->lock);
	now = get_timestamp_us();
	if (philosopher->setup->simulation_start_time > now)
		usleep_wrap(philosopher->setup->simulation_start_time - now);
	philosopher->start_of_last_meal = get_timestamp_us();
	pthread_mutex_unlock(&philosopher->lock);
	while (eating(philosopher) == SUCCESS
		&& sleeping(philosopher) == SUCCESS
		&& thinking(philosopher) == SUCCESS)
	{
		if (simulation_ended(SINGLETON_GET_VALUE) == true)
			break ;
	}
	return (arg);
}
