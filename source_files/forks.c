/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 16:52:27 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 12:48:13 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <errno.h>
#include "helpers.h"

/*
	Assigns forks to the philosophers.
	To print who got which fork, add this to the end of this function

	int32_t	i = 0;
	char	first = 'x';
	char	second = 'x';
	while (i < setup_values.num_philosophers)
	{
		if (philosopher->first_fork == setup_values.forks[i])
			first = i;
		if (philosopher->second_fork == setup_values.forks[i])
			second = i;
		i++;
	}
	printf("%2i\t%i\t%i\n", index, first, second);

	L = last fork
	I = index
	    2         3         4         5         6       <- Num philos
	I | f   l   | f   l   | f   l   | f   l   | f   l
	--------------------------------------------------
	0 | L   I   | L   I   | L   I   | L   I   | L   I
	1 | I   I-1 | I   I-1 | I   I-1 | I   I-1 | I   I-1
	2 |         | I   I-1 | I-1 I   | I-1 I   | I-1 I
	3 |                   | I   I-1 | I   I-1 | I   I-1
	4 |                             | I   I-1 | I-1 I
	5 |                                       | I   I-1
*/

void	assign_forks_to_philosopher(
		t_philo	*philosopher,
		t_philo_setup setup_values
	)
{
	const int32_t			index = philosopher->index - 1;
	pthread_mutex_t **const	forks = setup_values.forks;

	if (index == 0)
	{
		philosopher->first_fork = forks[setup_values.num_philosophers - 1];
		philosopher->second_fork = forks[index];
		return ;
	}
	if (index & 1 || index == setup_values.num_philosophers - 1)
	{
		philosopher->first_fork = forks[index];
		philosopher->second_fork = forks[index - 1];
		return ;
	}
	philosopher->first_fork = forks[index - 1];
	philosopher->second_fork = forks[index];
}

int32_t	destroy_fork(pthread_mutex_t **target)
{
	int32_t	mutex_destroy_return;

	mutex_destroy_return = pthread_mutex_destroy(*target);
	while (mutex_destroy_return)
	{
		if (mutex_destroy_return == EINVAL)
			break ;
		if (mutex_destroy_return == EBUSY)
		{
			usleep(100);
			mutex_destroy_return = pthread_mutex_destroy(*target);
		}
	}
	free(*target);
	*target = NULL;
	return (mutex_destroy_return);
}

int32_t	create_fork(pthread_mutex_t **target)
{
	int32_t	mutex_init_return;

	*target = malloc_wrap(sizeof(**target));
	if (*target == NULL)
		return (ALLOC_FAILED);
	mutex_init_return = pthread_mutex_init(*target, NULL);
	if (mutex_init_return != 0)
	{
		free(*target);
		*target = NULL;
	}
	return (mutex_init_return);
}

void	*destroy_forks(pthread_mutex_t **array)
{
	int32_t	i;

	i = 0;
	while (array[i])
	{
		destroy_fork(&array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

int32_t	create_forks(
		pthread_mutex_t ***fork_array,
		const int32_t num_philosophers
	)
{
	int32_t	i;
	int32_t	newfork;

	*fork_array = malloc_wrap(sizeof(**fork_array)
			* (num_philosophers + 1));
	if (*fork_array == NULL)
		return (-1);
	i = 0;
	while (i < num_philosophers)
	{
		newfork = create_fork(&(*fork_array)[i]);
		if (newfork != 0)
		{
			*fork_array = destroy_forks(*fork_array);
			return (newfork);
		}
		i++;
	}
	(*fork_array)[i] = NULL;
	return (0);
}
