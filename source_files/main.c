/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:37:02 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 13:49:35 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "datastructures.h"
#include "validate_input.h"
#include "forks.h"
#include "philosophers.h"
#include "debug.h"
#include "helpers.h"
#include "testing.h"
#include "cleanup.h"

/*
	Arguments to the function:
	1 - num_philosophers
	2 - time_to_die
	3 - time_to_eat
	4 - time_to_sleep
	5 - [number_of_times_each_philosopher_must_eat] (optional)
*/

int	main(int argc, char const *argv[])
{
	t_philo_setup	setup_values;
	int32_t			status;

	if (test_all(RUN_TESTS, LOG_ALL) == false && STOP_AFTER_TEST_FAIL)
		return (output_error(TEST_FAILED, output_to_stderr));
	if (argc != 5 && argc != 6)
		return (output_error(BAD_ARGC, output_to_stderr));
	if (parse_philosopher_program_input(&setup_values, argc, argv) != SUCCESS)
		return (output_error(BAD_INPUT, output_to_stderr));
	if (setup_values.number_of_times == 0)
		return (SUCCESS);
	if (create_forks(&(setup_values.forks), setup_values.num_philosophers))
		return (output_error(FORK_CREATION_FAILED, output_to_stderr));
	status = init_setup(&setup_values);
	if (status != SUCCESS)
		return (output_error(status, output_to_stderr));
	status = create_philosophers(&setup_values);
	if (status != SUCCESS)
	{
		cleanup_after_simulation(&setup_values);
		return (output_error(status, output_to_stderr));
	}
	return (cleanup_after_simulation(&setup_values));
}
