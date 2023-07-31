/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   helpers.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 13:28:27 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 15:07:02 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_H
# define HELPERS_H

# include <stddef.h>
# include "status.h"
# include "philosophers.h"

long long	ft_strtoll(const char *str, char **endptr, int base);
int			ft_nbrtostr_n(char *dst, uint64_t nbr, uint32_t nbrlen);
int32_t		ft_nbrlen_u(uint64_t value);
int32_t		simulation_ended(enum e_singleton_action action);

int			output_error(enum e_status status,
				int (*output)(const char *str, ...));

int32_t		init_setup(t_philo_setup *setup_values);

enum	e_helper_threads
{
	WRITER_THREAD,
	OBSERVER_THREAD,
	HELPER_THREAD_MAX
};

// ALLOCATION
enum	e_maybe_fail_allocation
{
	ALLOC_SET_N,
	ALLOC_DO_NOT_FAIL,
	ALLOC_GET_SHOULD_FAIL
};

bool		should_alloc_fail(enum e_maybe_fail_allocation action, int num);
void		*malloc_wrap(size_t	size);
void		*calloc_wrap(size_t count, size_t size);

#endif
