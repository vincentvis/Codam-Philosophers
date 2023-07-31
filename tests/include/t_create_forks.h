/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_create_forks.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 16:45:47 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/15 16:04:35 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_CREATE_FORKS_H
# define T_CREATE_FORKS_H

bool	test_creating_forks_returns_n_philos(int log_level);
bool	test_create_single_fork(int log_level);
bool	test_fail_alloc_single_fork(int log_level);
bool	test_nth_fork_mutex_fail(int log_level);

#endif
