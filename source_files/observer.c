/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   observer.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 17:12:27 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 17:56:42 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <pthread.h>
#include "datastructures.h"
#include "helpers.h"
#include "philo_time.h"
#include "status.h"
#include "writer.h"

__attribute__((always_inline))
static uint64_t	get_lmt(t_philo *philosopher)
{
	uint64_t	lmt;

	pthread_mutex_lock(&philosopher->lock);
	lmt = philosopher->start_of_last_meal;
	pthread_mutex_unlock(&philosopher->lock);
	return (lmt);
}

int32_t	death(t_philo *const philosopher)
{
	simulation_ended(SINGLETON_A);
	writer_mutex(SINGLETON_A);
	pthread_mutex_lock(&philosopher->lock);
	if (philosopher->setup->number_of_times == -1
		|| philosopher->times_eaten < philosopher->setup->number_of_times)
	{
		printf("%lli %i died\n", get_relative_time(
				philosopher->setup->simulation_start_time) - 1,
			philosopher->index);
	}
	philosopher->alive = false;
	pthread_mutex_unlock(&philosopher->lock);
	return (1);
}

__attribute__((always_inline))
static int32_t	is_full(t_philo *const philosopher)
{
	int32_t	times;

	pthread_mutex_lock(&philosopher->lock);
	times = philosopher->times_eaten;
	pthread_mutex_unlock(&philosopher->lock);
	return (philosopher->setup->number_of_times == times);
}

void	*observer_routine(void *arg)
{
	t_philo *const			philosophers = arg;
	t_philo_setup *const	setup = philosophers->setup;
	int32_t					i;
	int64_t					lmt;

	pthread_mutex_lock(philosophers[0].setup->global_event);
	pthread_mutex_unlock(philosophers[0].setup->global_event);
	usleep_wrap(setup->time_to_die / 2 * 1000);
	while (1)
	{
		i = 0;
		while (i < setup->num_philosophers
			&& simulation_ended(SINGLETON_GET_VALUE) == 0)
		{
			lmt = get_relative_time(get_lmt(&philosophers[i]));
			if (is_full(&philosophers[i]) == false
				&& lmt > setup->time_to_die && death(&philosophers[i]))
				return (arg);
			i++;
		}
		usleep(75);
	}
	return (arg);
}
