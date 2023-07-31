/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 17:09:54 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 13:46:32 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include "datastructures.h"
#include "helpers.h"
#include "philo_time.h"
#include "status.h"
#include "writer.h"
#include "cleanup.h"
#include "forks.h"

static int32_t	create_philosopher(
		t_philo *philosopher,
		t_philo_setup *setup_values,
		int32_t index
	)
{
	philosopher->index = index + 1;
	philosopher->alive = true;
	philosopher->setup = setup_values;
	if (pthread_mutex_init(&philosopher->lock, NULL) != SUCCESS)
		return (MUTEX_INIT_FAILED);
	assign_forks_to_philosopher(philosopher, *setup_values);
	if (pthread_create(&philosopher->self, NULL, philosopher_routine,
			philosopher) != SUCCESS)
		return (THREAD_CREATION_FAILED);
	return (SUCCESS);
}

static void	set_start_time(t_philo_setup *setup_values)
{
	setup_values->init_timestamp = get_timestamp_us();
	setup_values->simulation_start_time = setup_values->init_timestamp
		+ (setup_values->num_philosophers * PER_PHILO_START_OFFSET);
}

static int32_t	create_helper_threads(
		pthread_t helpers[HELPER_THREAD_MAX],
		t_philo *const philosophers
	)
{
	if (pthread_create(&helpers[WRITER_THREAD], NULL, writer_routine,
			philosophers->setup) != SUCCESS)
		return (THREAD_CREATION_FAILED);
	pthread_detach(helpers[WRITER_THREAD]);
	if (pthread_create(&helpers[OBSERVER_THREAD], NULL, observer_routine,
			philosophers) != SUCCESS)
		return (THREAD_CREATION_FAILED);
	pthread_detach(helpers[OBSERVER_THREAD]);
	return (SUCCESS);
}

int32_t	create_philosophers(
		t_philo_setup *setup
	)
{
	int32_t			status;
	int32_t			i;
	t_philo *const	philosophers = calloc_wrap(sizeof(*philosophers),
			setup->num_philosophers);
	pthread_t		helpers[HELPER_THREAD_MAX];

	if (philosophers == NULL)
		return (ALLOC_FAILED);
	pthread_mutex_lock(setup->global_event);
	i = 0;
	while (i < setup->num_philosophers)
	{
		status = create_philosopher(&philosophers[i], setup, i);
		if (status != SUCCESS)
			return (philo_create_fail(philosophers, setup, i, status));
		i++;
	}
	status = create_helper_threads(helpers, philosophers);
	if (status != SUCCESS)
		return (philo_create_fail(philosophers, setup, i, status));
	set_start_time(setup);
	pthread_mutex_unlock(setup->global_event);
	join_philosophers(philosophers, setup, setup->num_philosophers);
	return (SUCCESS);
}
