/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/18 14:33:59 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 10:48:20 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include "debug.h"

int	output_error(enum e_status status, int (*output)(const char *str, ...))
{
	static const char	*msgs[STATUS_MAX] = {
	[SUCCESS] = "",
	[BAD_ARGC] = "Wrong number of arguments\n",
	[BAD_INPUT] = "Bad input\n",
	[ALLOC_FAILED] = "An allocation failed\n",
	[RESOURCE_PROBLEM] = "An resource could not be created"
		"(alloc/mutex/thread)\n",
	[FORK_CREATION_FAILED] = "Failed to create mutexes for forks\n",
	[THREAD_CREATION_FAILED] = "Failed to create thread\n",
	[MUTEX_INIT_FAILED] = "Failed to initialize mutex\n",
	[MUTEX_DESTROY_FAILED] = "Failed to destroy mutex\n",
	[MUTEX_NOT_INITIALIZED] = "Tried to use uninitialized mutex\n",
	[TEST_FAILED] = "Configured to stop after a failed test\n"
	};

	if (status == SUCCESS)
		return (status);
	if (output == NULL)
		output = printf;
	if (msgs[status] != NULL)
		output(msgs[status]);
	return (status);
}
