/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc_wrap.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:41:02 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 14:27:45 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

#define TEST_NAME "alloc wrap"

static t_test	*get_tests(void)
{
	static t_test	tests[] = {
		&test_simple_malloc,
		&test_fail_first_malloc,
		&test_fail_third_malloc,
		&test_simple_calloc,
		&test_fail_fifth_calloc,
		NULL
	};

	return (tests);
}

bool	test_alloc_wrap(int log_level, int *successes, int *fails)
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
