/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:41:02 by vvissche      #+#    #+#                 */
/*   Updated: 2022/07/26 16:46:48 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "validate_input.h"
#include "t_validate_input.h"

#define TEST_NAME "check args"

static t_test	*get_tests(void)
{
	static t_test	tests[] = {
		&test_invalid_value_not_setting_variable,
		&test_negative_value_returning_false,
		&test_non_digit_in_input_returns_false,
		&test_assign_all_five_values,
		&test_long_max_plus_one_errno,
		NULL
	};

	return (tests);
}

bool	test_check_arg(int log_level, int *successes, int *fails)
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
