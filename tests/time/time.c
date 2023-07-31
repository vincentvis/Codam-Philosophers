/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 15:39:45 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:30:24 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "t_time.h"

#define TEST_NAME "time utils"

static t_test	*get_tests(void)
{
	static t_test	tests[] = {
		&test_get_timestamp_in_us,
		NULL
	};

	return (tests);
}

bool	test_time_utils(int log_level, int *successes, int *fails)
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
