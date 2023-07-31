/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo_time.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/17 14:05:08 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/11 14:53:39 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <unistd.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/types.h>

# define TIME_MULTIPLIER 1000000
# define TIME_OUTPUT_MULTIPLIER 1000
# define MAX_STEP_AMOUNT 4000

int64_t		get_relative_time(int64_t start);
int64_t		get_timestamp_us(void);
uint32_t	usleep_wrap(uint32_t time_to_sleep);

#endif
