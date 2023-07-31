/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/09 12:39:59 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 14:26:55 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "philo_time.h"
#include "helpers.h"
#include "message_queue.h"

void	queue_msg_event(
		t_philo *const philosopher,
		enum e_philosopher_state action)
{
	queue_enqueue(philosopher->setup->message_queue,
		(t_message){
		.action = action,
		.index = philosopher->index,
		.timestamp = get_relative_time(
			philosopher->setup->simulation_start_time)
	});
}
