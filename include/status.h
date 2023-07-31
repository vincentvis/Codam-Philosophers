/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   status.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/15 11:48:40 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/16 10:47:57 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATUS_H
# define STATUS_H

enum e_status {
	SUCCESS = 0,
	BAD_ARGC,
	BAD_INPUT,
	ALLOC_FAILED,
	RESOURCE_PROBLEM,
	FORK_CREATION_FAILED,
	THREAD_CREATION_FAILED,
	THREAD_JOIN_FAILED,
	MUTEX_INIT_FAILED,
	MUTEX_DESTROY_FAILED,
	MUTEX_NOT_INITIALIZED,
	PHILOSOPHER_DIED,
	SIMULATION_ENDED,
	PHILOSOPHER_IS_FULL,
	TEST_FAILED,
	STATUS_MAX
};

#endif
