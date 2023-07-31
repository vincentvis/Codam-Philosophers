/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   message_queue.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/10 14:16:39 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 14:35:02 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGE_QUEUE_H
# define MESSAGE_QUEUE_H

# include <stdint.h>
# include "datastructures.h"

int32_t		queue_init(t_philo_setup *setup, uint32_t size);
t_queue		*queue_destroy(t_queue *queue);
t_message	*queue_enqueue(t_queue *queue, t_message message);
t_message	queue_dequeue(t_queue *queue);

#endif
