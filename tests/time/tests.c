/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 14:00:22 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:09:45 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"
#include "philo_time.h"

// only tests if the get_timestamp_us function gets a timestamp that increases
// when called twice with a slight delay

bool	test_get_timestamp_in_us(int log_level)
{
	const uint64_t	timestamp1 = get_timestamp_us();
	const uint32_t	slept = usleep(5);
	const uint64_t	timestamp2 = get_timestamp_us();

	if (timestamp1 >= timestamp2)
	{
		return (log_test_failure_message(log_level, __FUNCTION__,
				"t1 is larger/equal to t2, t1 is expected to be smaller"));
	}
	(void)slept;
	return (log_test_success_message(log_level, __FUNCTION__));
}
