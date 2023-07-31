/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:30:05 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 18:04:56 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "helpers.h"
#include "philosophers.h"
#include "message_queue.h"
#include "writer.h"

__attribute__((pure))
static const char	*get_action_msg(enum e_philosopher_state index)
{
	static const char	*action_messages[] = {
		" " DEATH_MESSAGE "\n",
		" " TAKENFORK_MESSAGE "\n",
		" " EATING_MESSAGE "\n",
		" " SLEEPING_MESSAGE "\n",
		" " THINKING_MESSAGE "\n",
	};

	return (action_messages[index]);
}

/*
	Defined strings are fully known to the preprocessor
	A common preprocessor macro is:
	# define NUM_ELEMS(array) (sizeof(array) / sizeof(array[0]))
	Since our #define'd string is just a char array we get the stringlength
	of preprocessor defined strings INCLUDING the '\0'!!

	Since our message includes a starting space and a trailing newline
	we techincally subtract 1 for the '\0' and add 2 for the two other chars
*/

__attribute__((pure))
static size_t	get_actionmsg_size(enum e_philosopher_state index)
{
	static const size_t	action_message_lenghts[] = {
		(sizeof(DEATH_MESSAGE) / sizeof(DEATH_MESSAGE[0])) + 1,
		(sizeof(TAKENFORK_MESSAGE) / sizeof(TAKENFORK_MESSAGE[0])) + 1,
		(sizeof(EATING_MESSAGE) / sizeof(EATING_MESSAGE[0])) + 1,
		(sizeof(SLEEPING_MESSAGE) / sizeof(SLEEPING_MESSAGE[0])) + 1,
		(sizeof(THINKING_MESSAGE) / sizeof(THINKING_MESSAGE[0])) + 1,
	};

	return (action_message_lenghts[index]);
}

int32_t	writer_mutex(enum e_singleton_action action)
{
	static pthread_mutex_t	mutex;

	if (action == SINGLETON_INIT)
	{
		if (pthread_mutex_init(&mutex, NULL) != 0)
			return (MUTEX_INIT_FAILED);
	}
	if (action == SINGLETON_DESTROY)
	{
		if (pthread_mutex_destroy(&mutex) != 0)
			return (MUTEX_DESTROY_FAILED);
	}
	if (action == SINGLETON_A)
		return (pthread_mutex_lock(&mutex));
	if (action == SINGLETON_B)
		return (pthread_mutex_unlock(&mutex));
	return (SUCCESS);
}

void	output_philo_status(t_message msg)
{
	char					string[42];
	const int32_t			lengths[2] = {
		ft_nbrtostr_n(string, msg.timestamp, ft_nbrlen_u(msg.timestamp)),
		ft_nbrtostr_n(&string[lengths[0] + 1], msg.index,
			ft_nbrlen_u(msg.index))};

	string[lengths[0]] = ' ';
	writer_mutex(SINGLETON_A);
	if (simulation_ended(SINGLETON_GET_VALUE) > 1)
	{
		writer_mutex(SINGLETON_B);
		return ;
	}
	if (simulation_ended(SINGLETON_GET_VALUE) == 1)
		simulation_ended(SINGLETON_A);
	write(1, string, lengths[0] + lengths[1] + 1);
	write(1, get_action_msg(msg.action), get_actionmsg_size(msg.action));
	writer_mutex(SINGLETON_B);
}

void	*writer_routine(void *arg)
{
	t_message				message;
	t_philo_setup *const	setup = arg;
	t_queue *const			queue = setup->message_queue;
	bool					end_writer;

	pthread_mutex_lock(setup->global_event);
	end_writer = setup->end_writer;
	pthread_mutex_unlock(setup->global_event);
	while (end_writer == false)
	{
		message = queue_dequeue(queue);
		if (message.action != -1)
			output_philo_status(message);
		usleep(90);
		pthread_mutex_lock(setup->global_event);
		end_writer = setup->end_writer;
		pthread_mutex_unlock(setup->global_event);
	}
	return (arg);
}
