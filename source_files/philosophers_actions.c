/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers_actions.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 12:20:58 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 11:41:18 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "datastructures.h"
#include "helpers.h"
#include "philo_time.h"

static void	take_fork(pthread_mutex_t *fork, t_philo *const philosopher)
{
	pthread_mutex_lock(fork);
	queue_msg_event(philosopher, TAKINGFORK);
}

int32_t	eating(t_philo *const philosopher)
{
	take_fork(philosopher->first_fork, philosopher);
	take_fork(philosopher->second_fork, philosopher);
	pthread_mutex_lock(&philosopher->lock);
	philosopher->start_of_last_meal = get_timestamp_us();
	pthread_mutex_unlock(&philosopher->lock);
	queue_msg_event(philosopher, EATING);
	usleep_wrap(philosopher->setup->time_to_eat * TIME_OUTPUT_MULTIPLIER);
	pthread_mutex_lock(&philosopher->lock);
	philosopher->times_eaten++;
	pthread_mutex_unlock(&philosopher->lock);
	pthread_mutex_unlock(philosopher->first_fork);
	pthread_mutex_unlock(philosopher->second_fork);
	return (SUCCESS);
}

int32_t	thinking(t_philo *const philosopher)
{
	const int32_t	tts = philosopher->setup->time_to_sleep;
	const int32_t	tte = philosopher->setup->time_to_eat;

	queue_msg_event(philosopher, THINKING);
	if (philosopher->setup->num_philosophers & 1)
		usleep_wrap((tte * 2 - tts) * TIME_OUTPUT_MULTIPLIER);
	return (SUCCESS);
}

int32_t	sleeping(t_philo *const philosopher)
{
	queue_msg_event(philosopher, SLEEPING);
	usleep_wrap(philosopher->setup->time_to_sleep * TIME_OUTPUT_MULTIPLIER);
	if (philosopher->times_eaten == philosopher->setup->number_of_times)
		return (PHILOSOPHER_IS_FULL);
	return (SUCCESS);
}
