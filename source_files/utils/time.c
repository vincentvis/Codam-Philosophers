/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 13:58:37 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:24:24 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <sys/time.h>
#include <pthread.h>
#include <sys/types.h>
#include "philo_time.h"
#include "helpers.h"

int64_t	get_relative_time(int64_t start)
{
	const int64_t	diff = get_timestamp_us() - start;

	return ((diff - (diff % 1000)) / 1000);
}

int64_t	get_timestamp_us(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, DST_NONE);
	return (current_time.tv_usec + (current_time.tv_sec * TIME_MULTIPLIER));
}

uint32_t	usleep_wrap(uint32_t time_to_sleep)
{
	const int64_t	start = get_timestamp_us();
	const int64_t	target = start + time_to_sleep;
	const int64_t	subtarget = target - 3;
	int64_t			current;
	int64_t			step_amount;

	current = start;
	while (current < subtarget
		&& simulation_ended(SINGLETON_GET_VALUE) == 0)
	{
		step_amount = (((target - current) / 3) | 1);
		if (step_amount > MAX_STEP_AMOUNT)
			step_amount = MAX_STEP_AMOUNT;
		if (step_amount > 2)
			step_amount -= 1;
		usleep(step_amount);
		current = get_timestamp_us();
	}
	return (current - start);
}
