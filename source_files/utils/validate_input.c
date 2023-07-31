/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_input.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:16:50 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:07:39 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "helpers.h"
#include "datastructures.h"
#include <errno.h>

bool	check_arg(int32_t *const dest, char const *arg_str)
{
	char	*endptr;
	int64_t	num;
	int32_t	cast;

	num = ft_strtoll(arg_str, &endptr, 10);
	cast = num;
	if (num < 0 || num != cast || (endptr && *endptr != '\0') || errno != 0)
		return (false);
	*dest = cast;
	return (true);
}

int	parse_philosopher_program_input(t_philo_setup *setup_values,
	int argc, char const *argv[])
{
	int32_t *const		args[] = {
		&(setup_values->num_philosophers),
		&(setup_values->time_to_die),
		&(setup_values->time_to_eat),
		&(setup_values->time_to_sleep),
		&(setup_values->number_of_times),
		NULL};
	const uint32_t		num_args = argc - 1;
	uint32_t			i;

	i = 0;
	setup_values->number_of_times = -1;
	while (i < num_args)
	{
		if (check_arg(args[i], argv[i + 1]) == false)
			return (BAD_INPUT);
		i++;
	}
	return (SUCCESS);
}
