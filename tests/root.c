/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   root.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/19 15:37:29 by vvissche      #+#    #+#                 */
/*   Updated: 2022/07/26 16:28:31 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

static t_suite	*get_suites(void)
{
	static t_suite	suites[] = {
		&test_check_arg,
		&test_create_forks,
		&test_alloc_wrap,
		&test_time_utils,
		NULL
	};

	return (suites);
}

bool	test_all(bool run, int log_level)
{
	const t_suite	*suites = get_suites();
	size_t			i;
	int				successes;
	int				fails;

	if (run == false)
		return (true);
	if (log_level > LOG_NONE)
		printf(C_BLU "TESTING" C_RST "\n" SUITE_DIVIDER);
	successes = 0;
	fails = 0;
	i = 0;
	while (suites[i])
	{
		suites[i](log_level, &successes, &fails);
		i++;
	}
	log_final_result(log_level, successes, fails);
	should_alloc_fail(ALLOC_DO_NOT_FAIL, 0);
	if (fails > 0)
		return (false);
	return (true);
}
