/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 16:14:40 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 16:48:44 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "forks.h"
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define WRNG_FRK "Wrong number of forks returned"
#define FRKA_NLL "Fork array is NULL (alloc failed?)"
#define NUM_PHILO_T1 10

bool	test_creating_forks_returns_n_philos(int log_level)
{
	pthread_mutex_t	**fork_array;
	int32_t			i;
	bool			fail_pass;
	const int32_t	result = create_forks(&fork_array, NUM_PHILO_T1);

	fail_pass = true;
	if (result != 0)
		fail_pass = log_test_failure_message(log_level, __FUNCTION__, WRNG_FRK);
	if (fork_array == NULL)
		fail_pass = log_test_failure_message(log_level, __FUNCTION__, FRKA_NLL);
	i = 0;
	while (fail_pass && i < NUM_PHILO_T1)
	{
		if (fork_array[i] == NULL)
			fail_pass = log_test_failure_message(log_level, __FUNCTION__,
					"Fork in array equals NULL where it should not");
		i++;
	}
	if (fork_array[i] != NULL)
		fail_pass = log_test_failure_message(log_level, __FUNCTION__,
				NO_NULLTERM);
	fork_array = destroy_forks(fork_array);
	if (fail_pass)
		return (log_test_success_message(log_level, __FUNCTION__));
	return (false);
}

#undef WRNG_FRK
#undef FRKA_NLL
#undef NUM_PHILO_T1

bool	test_create_single_fork(int log_level)
{
	pthread_mutex_t	*mutex;
	const int32_t	init_result = create_fork(&mutex);
	int32_t			destroy_result;

	if (init_result != 0)
	{
		if (init_result == ALLOC_FAILED)
			log_test_failure_message(log_level, __FUNCTION__, UNEXP_ALLOC_FAIL);
		else if (init_result != 0)
			log_test_failure_message(log_level, __FUNCTION__,
				"Mutex init non zero return value");
		if (mutex != NULL)
			log_test_failure_message(log_level, __FUNCTION__,
				"Mutex variable is not NULL");
	}
	destroy_result = destroy_fork(&mutex);
	if (destroy_result == 0 && mutex == NULL)
		return (log_test_success_message(log_level, __FUNCTION__));
	if (mutex != NULL)
		log_test_failure_message(log_level, __FUNCTION__,
			"Mutex not set to NULL after destroying");
	if (destroy_result != 0)
		log_test_failure_message(log_level, __FUNCTION__,
			"pthread_mutex_destroy gave non zero return value");
	return (false);
}

bool	test_fail_alloc_single_fork(int log_level)
{
	pthread_mutex_t	*mutex;
	int32_t			result;

	mutex = NULL;
	should_alloc_fail(ALLOC_SET_N, 1);
	result = create_fork(&mutex);
	if (result == ALLOC_FAILED && mutex == NULL)
		return (log_test_success_message(log_level, __FUNCTION__));
	return (log_test_failure_message(log_level, __FUNCTION__,
			UNEXP_ALLOC_SUCC));
}

bool	test_nth_fork_mutex_fail(int log_level)
{
	pthread_mutex_t	**fork_array;
	int32_t			init_result;
	bool			r;

	should_alloc_fail(ALLOC_SET_N, 3);
	r = true;
	init_result = create_forks(&fork_array, 5);
	if (init_result != ALLOC_FAILED)
		r = log_test_failure_message(log_level, __FUNCTION__, UNEXP_ALLOC_SUCC);
	if (fork_array != NULL)
		r = log_test_failure_message(log_level, __FUNCTION__,
				"Fork array should be NULL");
	if (r)
		return (log_test_success_message(log_level, __FUNCTION__));
	return (r);
}
