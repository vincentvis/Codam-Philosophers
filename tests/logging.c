/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logging.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 13:14:51 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/17 20:08:07 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

void	log_final_result(int log_level, int success, int fail)
{
	if (log_level & LOG_RESULT)
	{
		printf(C_BLU "%-25s\t" C_RST
			C_GRN "success: %i\t" C_RST
			C_RED_B "fails: %i\n" C_RST
			SUITE_DIVIDER,
			"Testing done", success, fail);
	}
}

void	log_test_result(int log_level, const char *test_name,
	int success, int fail)
{
	if (log_level & LOG_SUB_RESULT)
	{
		if (fail > 0)
		{
			printf(C_RED);
		}
		else
		{
			printf(C_GRN);
		}
		printf("SUITE:%-25s\t" C_RST
			C_GRN "success: %i\t" C_RST
			C_RED "fails: %i\n" C_RST
			SUITE_DIVIDER,
			test_name, success, fail);
	}
}

bool	log_test_failure_message(int log_level, const char *function_name,
		const char *message)
{
	if (log_level & LOG_FAILURES)
	{
		printf(C_RED "%-39s" C_RST ": %s\n", function_name + 5, message);
	}
	return (false);
}

bool	log_test_success_message(int log_level, const char *function_name)
{
	if (log_level & LOG_SUCCESS)
	{
		printf(C_GRN "%-39s" C_RST ": success\n", function_name + 5);
	}
	return (true);
}

bool	log_test_todo(int log_level, const char *function_name)
{
	if (log_level & LOG_TODO)
	{
		printf(C_CYA_BU "%-39s: TODO" C_RST "\n", function_name + 5);
	}
	return (false);
}
