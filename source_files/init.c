/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 15:02:17 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 13:38:24 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "datastructures.h"
#include "philosophers.h"
#include "helpers.h"
#include "message_queue.h"
#include "writer.h"
#include "forks.h"

static int32_t	init_global_event_mutex(t_philo_setup *setup_values)
{
	int32_t	status;

	setup_values->terminate = false;
	setup_values->end_writer = false;
	setup_values->global_event = malloc_wrap(
			sizeof(*setup_values->global_event));
	if (setup_values->global_event == NULL)
		return (ALLOC_FAILED);
	status = pthread_mutex_init(setup_values->global_event, NULL);
	if (status != SUCCESS)
	{
		free(setup_values->global_event);
		return (status);
	}
	return (SUCCESS);
}

static int32_t	init_fail(
		t_philo_setup *setup_values,
		int32_t status,
		int32_t where)
{
	if (where >= 3)
		simulation_ended(SINGLETON_DESTROY);
	if (where >= 2)
	{
		pthread_mutex_destroy(setup_values->global_event);
		free(setup_values->global_event);
	}
	if (where >= 1)
		writer_mutex(SINGLETON_DESTROY);
	destroy_forks(setup_values->forks);
	return (status);
}

int32_t	init_setup(t_philo_setup *setup_values)
{
	int32_t	status;

	status = writer_mutex(SINGLETON_INIT);
	if (status != SUCCESS)
		return (init_fail(setup_values, status, 0));
	status = init_global_event_mutex(setup_values);
	if (status != SUCCESS)
		return (init_fail(setup_values, status, 1));
	if (simulation_ended(SINGLETON_INIT) == MUTEX_INIT_FAILED)
		return (init_fail(setup_values, MUTEX_INIT_FAILED, 2));
	status = queue_init(setup_values,
			setup_values->num_philosophers * 5 * QUEUE_MULTIPLIER);
	if (status != SUCCESS)
		return (init_fail(setup_values, MUTEX_INIT_FAILED, 3));
	return (SUCCESS);
}
