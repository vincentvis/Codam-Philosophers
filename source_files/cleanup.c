/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 18:25:05 by vincent       #+#    #+#                 */
/*   Updated: 2022/08/16 18:05:40 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include "datastructures.h"
#include "status.h"
#include "message_queue.h"
#include "forks.h"
#include "helpers.h"
#include "writer.h"

void	wait_for_empty_queue(t_queue *queue)
{
	if (simulation_ended(SINGLETON_GET_VALUE) >= 1)
		return ;
	while (1)
	{
		pthread_mutex_lock(&queue->locks[Q_DEQUEUE]);
		pthread_mutex_lock(&queue->locks[Q_ENQUEUE]);
		if (queue->index[Q_DEQUEUE] != queue->index[Q_ENQUEUE])
		{
			pthread_mutex_unlock(&queue->locks[Q_DEQUEUE]);
			pthread_mutex_unlock(&queue->locks[Q_ENQUEUE]);
			usleep(250);
		}
		else
		{
			pthread_mutex_unlock(&queue->locks[Q_DEQUEUE]);
			pthread_mutex_unlock(&queue->locks[Q_ENQUEUE]);
			break ;
		}
	}
}

int32_t	join_philosophers(
		t_philo *philosophers,
		t_philo_setup *setup_values,
		int32_t n_philo
	)
{
	int32_t	i;
	int32_t	return_value;
	t_philo	*philosopher;

	i = 0;
	return_value = 0;
	while (i < n_philo)
	{
		if (pthread_join(philosophers[i].self,
				(void**)&philosopher) != SUCCESS)
			return_value = THREAD_JOIN_FAILED;
		i++;
	}
	wait_for_empty_queue(setup_values->message_queue);
	pthread_mutex_lock(setup_values->global_event);
	setup_values->end_writer = true;
	pthread_mutex_unlock(setup_values->global_event);
	free(philosophers);
	return (return_value);
}

int	cleanup_after_simulation(t_philo_setup *setup_values)
{
	destroy_forks(setup_values->forks);
	pthread_mutex_lock(setup_values->global_event);
	setup_values->end_writer = true;
	pthread_mutex_unlock(setup_values->global_event);
	usleep(100);
	writer_mutex(SINGLETON_DESTROY);
	pthread_mutex_destroy(setup_values->global_event);
	free(setup_values->global_event);
	simulation_ended(SINGLETON_DESTROY);
	setup_values->message_queue = queue_destroy(setup_values->message_queue);
	return (0);
}

int32_t	philo_create_fail(
		t_philo *philosophers,
		t_philo_setup *setup_values,
		int32_t index,
		int32_t status
	)
{
	int32_t	i;

	setup_values->terminate = true;
	simulation_ended(SINGLETON_A);
	simulation_ended(SINGLETON_A);
	i = 0;
	while (i < index)
	{
		pthread_mutex_destroy(&(philosophers[i].lock));
		i++;
	}
	pthread_mutex_unlock(setup_values->global_event);
	join_philosophers(philosophers, setup_values, index);
	free(philosophers);
	return (status);
}
