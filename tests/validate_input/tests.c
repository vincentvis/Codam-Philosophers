/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests_1_5.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:46:02 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 18:25:41 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "testing.h"
#include "datastructures.h"
#include "validate_input.h"

// prototype of function, since it does not have to be exposed in a header
bool	check_arg(int32_t *const dest, char const *arg_str);

bool	test_invalid_value_not_setting_variable(int log_level)
{
	int32_t			target;
	bool			return_value;
	const int32_t	expected = 25;
	const char		*input = "-1";
	const bool		expected_return = false;

	target = 25;
	return_value = check_arg(&target, input);
	if (return_value == expected_return && target == expected)
		return (log_test_success_message(log_level, __FUNCTION__));
	if (return_value != expected_return)
		log_test_failure_message(log_level, __FUNCTION__, "wrong return value");
	if (target != expected)
		log_test_failure_message(log_level, __FUNCTION__, \
			"wrong value set in function");
	return (false);
}

bool	test_negative_value_returning_false(int log_level)
{
	int32_t		target;
	const bool	return_value = check_arg(&target, "-25");

	if (return_value == false)
		return (log_test_success_message(log_level, __FUNCTION__));
	return (log_test_failure_message(log_level, __FUNCTION__,
			"wrong return value"));
}

bool	test_long_max_plus_one_errno(int log_level)
{
	int32_t		target;
	const bool	return_value = check_arg(&target, "9223372036854775808");

	if (errno == ERANGE && return_value == false)
	{
		errno = 0;
		return (log_test_success_message(log_level, __FUNCTION__));
	}
	if (errno != ERANGE)
		log_test_failure_message(log_level, __FUNCTION__, "wrong errno value");
	if (return_value == true)
		log_test_failure_message(log_level, __FUNCTION__, "wrong return value");
	return (false);
}

bool	test_non_digit_in_input_returns_false(int log_level)
{
	int32_t		target;
	bool		return_value;

	target = 0;
	return_value = check_arg(&target, "25a");
	if (return_value == true)
		return (log_test_failure_message(log_level, __FUNCTION__,
				"wrong return value"));
	if (target != 0)
		return (log_test_failure_message(log_level, __FUNCTION__,
				"value should not be set"));
	return (log_test_success_message(log_level, __FUNCTION__));
}

bool	test_assign_all_five_values(int log_level)
{
	t_philo_setup	setup_values;
	const char		*argv[] = {"", "5", "700", "100", "200", "24", NULL};
	const int32_t	expected[] = {5, 700, 100, 200, 24};
	const int		argc = 6;

	if (parse_philosopher_program_input(&setup_values, argc, argv) != SUCCESS)
		return (log_test_failure_message(log_level, __FUNCTION__,
				"wrong return value"));
	if (setup_values.num_philosophers != expected[0]
		|| setup_values.time_to_die != expected[1]
		|| setup_values.time_to_eat != expected[2]
		|| setup_values.time_to_sleep != expected[3]
		|| setup_values.number_of_times != expected[4])
		return (log_test_failure_message(log_level, __FUNCTION__,
				"wrong value set"));
	return (log_test_success_message(log_level, __FUNCTION__));
}
