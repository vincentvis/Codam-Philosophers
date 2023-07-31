/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_forks.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:41:02 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 16:04:22 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "t_create_forks.h"

#define TEST_NAME "create forks"

static t_test	*get_tests(void)
{
	static t_test	tests[] = {
		&test_creating_forks_returns_n_philos,
		&test_create_single_fork,
		&test_fail_alloc_single_fork,
		&test_nth_fork_mutex_fail,
		NULL
	};

	return (tests);
}

bool	test_create_forks(int log_level, int *successes, int *fails)
{
	const t_test	*tests = get_tests();
	size_t			i;
	int				success;
	int				fail;

	i = 0;
	success = 0;
	fail = 0;
	while (tests[i])
	{
		should_alloc_fail(ALLOC_DO_NOT_FAIL, 0);
		if (tests[i](log_level) == true)
			success++;
		else
			fail++;
		i++;
	}
	*successes += success;
	*fails += fail;
	log_test_result(log_level, TEST_NAME, success, fail);
	if (fail != 0)
		return (false);
	return (true);
}
