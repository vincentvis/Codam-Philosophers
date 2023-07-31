/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tests.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 17:30:45 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:32:56 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "testing.h"

bool	test_simple_malloc(int log_level)
{
	void	*ptr;

	should_alloc_fail(ALLOC_DO_NOT_FAIL, 0);
	ptr = malloc_wrap(5);
	if (ptr != NULL)
	{
		free(ptr);
		return (log_test_success_message(log_level, __FUNCTION__));
	}
	return (log_test_failure_message(log_level, __FUNCTION__,
			UNEXP_ALLOC_FAIL));
}

bool	test_fail_first_malloc(int log_level)
{
	void	*ptr;

	if (should_alloc_fail(ALLOC_SET_N, 1) != false)
		return (log_test_failure_message(log_level, __FUNCTION__,
				"alloc fail static function failed to set value"));
	ptr = malloc_wrap(5);
	if (ptr == NULL)
		return (log_test_success_message(log_level, __FUNCTION__));
	free(ptr);
	return (log_test_failure_message(log_level, __FUNCTION__,
			UNEXP_ALLOC_SUCC));
}

bool	test_fail_third_malloc(int log_level)
{
	size_t	i;
	void	*ptr;

	should_alloc_fail(ALLOC_SET_N, 3);
	i = 1;
	while (i < 8)
	{
		ptr = malloc_wrap(2 * sizeof(void *));
		if (i == 3 && ptr != NULL)
		{
			free(ptr);
			return (log_test_failure_message(log_level, __FUNCTION__,
					UNEXP_ALLOC_SUCC));
		}
		if (i != 3 && ptr == NULL)
			return (log_test_failure_message(log_level, __FUNCTION__,
					UNEXP_ALLOC_FAIL));
		free(ptr);
		ptr = NULL;
		i++;
	}
	return (log_test_success_message(log_level, __FUNCTION__));
}

bool	test_simple_calloc(int log_level)
{
	int32_t	size;
	void	*ptr;

	should_alloc_fail(ALLOC_DO_NOT_FAIL, 0);
	ptr = calloc_wrap(2, sizeof(int32_t));
	if (ptr == NULL)
		return (log_test_failure_message(log_level, __FUNCTION__,
				UNEXP_ALLOC_FAIL));
	size = 2 * sizeof(int32_t);
	while (size--)
		if (((char *)ptr)[size] != 0)
			break ;
	free(ptr);
	if (size != -1)
		return (log_test_failure_message(log_level, __FUNCTION__,
				"Failed to bzero"));
	return (log_test_success_message(log_level, __FUNCTION__));
}

bool	test_fail_fifth_calloc(int log_level)
{
	size_t	i;
	void	*ptr;

	should_alloc_fail(ALLOC_SET_N, 5);
	i = 1;
	while (i < 8)
	{
		ptr = calloc_wrap(2, sizeof(void *));
		if (i == 5 && ptr != NULL)
		{
			free(ptr);
			return (log_test_failure_message(log_level, __FUNCTION__,
					UNEXP_ALLOC_SUCC));
		}
		if (i != 5 && ptr == NULL)
			return (log_test_failure_message(log_level, __FUNCTION__,
					UNEXP_ALLOC_FAIL));
		free(ptr);
		ptr = NULL;
		i++;
	}
	return (log_test_success_message(log_level, __FUNCTION__));
}
