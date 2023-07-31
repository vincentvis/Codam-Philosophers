/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alloc_wrap.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 17:07:14 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/13 18:58:05 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "helpers.h"

bool	should_alloc_fail(enum e_maybe_fail_allocation action, int num)
{
	static int	should_fail = 0;

	if (action == ALLOC_SET_N)
	{
		should_fail = num + 1;
		return (false);
	}
	if (action == ALLOC_DO_NOT_FAIL)
	{
		should_fail = 0;
		return (false);
	}
	if (should_fail > 0)
		should_fail--;
	return (should_fail == 1);
}

void	*malloc_wrap(size_t	size)
{
	if (should_alloc_fail(ALLOC_GET_SHOULD_FAIL, 0))
		return (NULL);
	return (malloc(size));
}

void	*calloc_wrap(size_t count, size_t size)
{
	void	*ptr;

	if (should_alloc_fail(ALLOC_GET_SHOULD_FAIL, 0))
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	memset(ptr, 0, (count * size));
	return (ptr);
}
