/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   datastructures.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:15:49 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 18:02:34 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATASTRUCTURES_H
# define DATASTRUCTURES_H

# include "status.h"
# include <stdint.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <stdbool.h>

# define PER_PHILO_START_OFFSET 200

enum e_philosopher_state {
	DEATH,
	TAKINGFORK,
	EATING,
	SLEEPING,
	THINKING,
	WAITING_TO_START
};

typedef struct s_message {
	int32_t		action;
	int32_t		index;
	uint64_t	timestamp;
}	t_message;

# define QUEUE_MULTIPLIER 10

enum	e_queue
{
	Q_ENQUEUE,
	Q_DEQUEUE,
	Q_MAX
};

typedef struct s_queue {
	uint32_t		size;
	t_message		*messages;
	uint32_t		index[Q_MAX];
	pthread_mutex_t	*locks;
}	t_queue;

typedef struct s_philo_setup {
	int32_t			num_philosophers;
	int32_t			time_to_die;
	int32_t			time_to_eat;
	int32_t			time_to_sleep;
	int32_t			number_of_times;
	int64_t			init_timestamp;
	int64_t			simulation_start_time;
	bool			terminate;
	bool			end_writer;
	pthread_mutex_t	*global_event;
	pthread_mutex_t	**forks;
	t_queue			*message_queue;
}				t_philo_setup;

typedef struct s_philo {
	uint32_t					index;
	int64_t						start_of_last_meal;
	pthread_mutex_t				*first_fork;
	pthread_mutex_t				*second_fork;
	pthread_mutex_t				lock;
	int32_t						times_eaten;
	bool						alive;
	t_philo_setup				*setup;
	pthread_t					self;
}	t_philo;

#endif
