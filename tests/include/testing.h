/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testing.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:39:26 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 10:47:28 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTING_H
# define TESTING_H

# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include "helpers.h"
# include "t_alloc_wrap.h"

# define NO_NULLTERM "Array is not NULL terminated"

enum e_log_levels {
	LOG_NONE,
	LOG_RESULT = 1,
	LOG_SUB_RESULT = 1 << 2,
	LOG_FAILURES = 1 << 3,
	LOG_SUCCESS = 1 << 4,
	LOG_TODO = 1 << 5,
	LOG_ALL_FAIL = LOG_RESULT | LOG_SUB_RESULT | LOG_FAILURES | LOG_TODO,
	LOG_ALL = LOG_ALL_FAIL | LOG_SUCCESS
};

# define C_RED "\033[31m"
# define C_RED_U "\033[4;31m"
# define C_RED_B "\033[1;31m"
# define C_GRN "\033[32m"
# define C_GRN_U "\033[4;32m"
# define C_BLU "\033[1;34m"
# define C_BLU_U "\033[4;34m"
# define C_GRY "\033[90m"
# define C_GRY_U "\033[4;90m"
# define C_CYA "\033[1;36m"
# define C_CYA_U "\033[4;36m"
# define C_CYA_B "\033[1;36m"
# define C_CYA_BU "\033[1;4;36m"
# define C_RST "\033[0m"
# define SUITE_DIVIDER "\033[0;90m\
────────────────────────────────────────────────────────\033[0m\n"

# define RUN_TESTS 0
# define STOP_AFTER_TEST_FAIL 0

bool		test_all(bool run, int log_level);

typedef bool	(*t_test)(int log_level);
typedef bool	(*t_suite)(int log_level, int *s, int *f);

// SUITES
bool		test_check_arg(int log_level, int *successes, int *fails);
bool		test_alloc_wrap(int log_level, int *successes, int *fails);
bool		test_create_forks(int log_level, int *successes, int *fails);
bool		test_time_utils(int log_level, int *successes, int *fails);

// LOGGING
void		log_final_result(int log_level, int success, int fail);
bool		log_test_todo(int log_level, const char *function_name);
bool		log_test_success_message(int log_level, const char *function_name);
bool		log_test_failure_message(int log_level, const char *function_name,
				const char *message);
void		log_test_result(int log_level, const char *test_name,
				int success, int fail);
void		log_suite_name(int log_level, const char *suite_name);

#endif
