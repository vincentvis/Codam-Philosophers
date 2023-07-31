/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:48:35 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 16:46:07 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "datastructures.h"
#include "debug.h"

int	output_to_stderr(const char *str, ...)
{
	va_list		ap;
	int			n;

	va_start(ap, str);
	n = vdprintf(2, str, ap);
	va_end(ap);
	return (n);
}

void	output_initialization_info(t_philo_setup setup_values,
	int (*output)(const char *str, ...))
{
	if (output == NULL)
		output = printf;
	output(
		"%24s : %4i\n"
		"%24s : %4i ms\n"
		"%24s : %4i ms\n"
		"%24s : %4i ms\n"
		"%24s : %4i\n",
		"num_philosophers", setup_values.num_philosophers,
		"time_to_die", setup_values.time_to_die,
		"time_to_eat", setup_values.time_to_eat,
		"time_to_sleep", setup_values.time_to_sleep,
		"number_of_times", setup_values.number_of_times);
}
