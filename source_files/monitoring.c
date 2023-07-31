/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   monitoring.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/02 15:01:22 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 17:58:15 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include "philosophers.h"
#include "datastructures.h"
#include "helpers.h"
#include "philo_time.h"
#include "writer.h"

bool	check_philo_state(t_philo *const philosopher)
{
	const uint64_t	now = get_timestamp_us();
	const int32_t	ttd = philosopher->setup->time_to_die * 1000;
	int32_t			time_since_last_meal;
	int32_t			times_eaten;

	pthread_mutex_lock(&philosopher->lock);
	times_eaten = philosopher->times_eaten;
	time_since_last_meal = now - philosopher->start_of_last_meal;
	pthread_mutex_unlock(&philosopher->lock);
	if (time_since_last_meal > ttd
		&& philosopher->times_eaten < philosopher->setup->number_of_times)
	{
		death(philosopher);
		return (PHILOSOPHER_DIED);
	}
	if (simulation_ended(SINGLETON_GET_VALUE) == true)
		return (SIMULATION_ENDED);
	return (SUCCESS);
}

int32_t	simulation_ended(enum e_singleton_action action)
{
	static pthread_mutex_t	mutex;
	static int32_t			has_deaths = 0;
	int32_t					return_value;

	return_value = 0;
	if (action == SINGLETON_INIT)
	{
		if (pthread_mutex_init(&mutex, NULL) != 0)
			return (MUTEX_INIT_FAILED);
		return (SUCCESS);
	}
	if (action == SINGLETON_DESTROY)
	{
		if (pthread_mutex_destroy(&mutex) != 0)
			return (MUTEX_DESTROY_FAILED);
		return (SUCCESS);
	}
	pthread_mutex_lock(&mutex);
	if (action == SINGLETON_A)
		has_deaths++;
	return_value = has_deaths;
	pthread_mutex_unlock(&mutex);
	return (return_value);
}
