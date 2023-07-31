/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message_queue.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:15:31 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 18:05:55 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

#include "philosophers.h"
#include "datastructures.h"
#include "helpers.h"
#include "status.h"
#include "writer.h"

#include <stdio.h>

static int32_t	setup_queue_locks(t_queue *queue)
{
	int32_t	status;

	queue->locks = malloc_wrap(sizeof(*queue->locks) * Q_MAX);
	if (queue->locks == NULL)
		return (ALLOC_FAILED);
	status = pthread_mutex_init(&queue->locks[Q_ENQUEUE], NULL);
	if (status != SUCCESS)
	{
		free(queue->messages);
		return (status);
	}
	status = pthread_mutex_init(&queue->locks[Q_DEQUEUE], NULL);
	if (status != SUCCESS)
	{
		pthread_mutex_destroy(&queue->locks[Q_ENQUEUE]);
		free(queue->messages);
		return (status);
	}
	return (SUCCESS);
}

int32_t	queue_init(t_philo_setup *setup, uint32_t size)
{
	int32_t	status;

	setup->message_queue = malloc_wrap(sizeof(*setup->message_queue));
	if (setup->message_queue == NULL)
		return (ALLOC_FAILED);
	setup->message_queue->size = size;
	setup->message_queue->messages = malloc_wrap(sizeof(
				*setup->message_queue->messages) * setup->message_queue->size);
	if (setup->message_queue->messages == NULL)
		return (ALLOC_FAILED);
	setup->message_queue->index[Q_ENQUEUE] = 0;
	setup->message_queue->index[Q_DEQUEUE] = 0;
	status = setup_queue_locks(setup->message_queue);
	if (status != SUCCESS)
		return (status);
	memset(setup->message_queue->messages, -1, sizeof(
			*setup->message_queue->messages) * setup->message_queue->size);
	return (SUCCESS);
}

t_queue	*queue_destroy(t_queue *queue)
{
	if (queue == NULL)
		return (NULL);
	free(queue->messages);
	if (pthread_mutex_destroy(&queue->locks[Q_ENQUEUE]) == EBUSY)
	{
		pthread_mutex_lock(&queue->locks[Q_ENQUEUE]);
		pthread_mutex_unlock(&queue->locks[Q_ENQUEUE]);
		pthread_mutex_destroy(&queue->locks[Q_ENQUEUE]);
	}
	if (pthread_mutex_destroy(&queue->locks[Q_DEQUEUE]) == EBUSY)
	{
		pthread_mutex_lock(&queue->locks[Q_DEQUEUE]);
		pthread_mutex_unlock(&queue->locks[Q_DEQUEUE]);
		pthread_mutex_destroy(&queue->locks[Q_DEQUEUE]);
	}
	free(queue->locks);
	free(queue);
	return (NULL);
}

t_message	*queue_enqueue(t_queue *queue, t_message message)
{
	uint32_t	new_message_index;

	pthread_mutex_lock(&queue->locks[Q_ENQUEUE]);
	new_message_index = queue->index[Q_ENQUEUE];
	queue->messages[new_message_index].action = message.action;
	queue->messages[new_message_index].index = message.index;
	queue->messages[new_message_index].timestamp = message.timestamp;
	queue->index[Q_ENQUEUE]++;
	if (queue->index[Q_ENQUEUE] >= queue->size)
		queue->index[Q_ENQUEUE] = 0;
	pthread_mutex_unlock(&queue->locks[Q_ENQUEUE]);
	return (&queue->messages[new_message_index]);
}

t_message	queue_dequeue(t_queue *queue)
{
	t_message	message;
	uint32_t	enqueue_index;

	pthread_mutex_lock(&queue->locks[Q_ENQUEUE]);
	enqueue_index = queue->index[Q_ENQUEUE];
	pthread_mutex_unlock(&queue->locks[Q_ENQUEUE]);
	message.action = -1;
	pthread_mutex_lock(&queue->locks[Q_DEQUEUE]);
	while (1)
	{
		if (queue->index[Q_DEQUEUE] == enqueue_index)
			break ;
		message.action = queue->messages[queue->index[Q_DEQUEUE]].action;
		queue->messages[queue->index[Q_DEQUEUE]].action = -1;
		message.index = queue->messages[queue->index[Q_DEQUEUE]].index;
		queue->messages[queue->index[Q_DEQUEUE]].index = -1;
		message.timestamp = queue->messages[queue->index[Q_DEQUEUE]].timestamp;
		queue->index[Q_DEQUEUE]++;
		if (queue->index[Q_DEQUEUE] >= queue->size)
			queue->index[Q_DEQUEUE] = 0;
		break ;
	}
	pthread_mutex_unlock(&queue->locks[Q_DEQUEUE]);
	return (message);
}
