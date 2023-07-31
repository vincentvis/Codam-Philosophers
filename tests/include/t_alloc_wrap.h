/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_alloc_wrap.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 17:35:30 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/13 18:54:16 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_ALLOC_WRAP_H
# define T_ALLOC_WRAP_H

# define UNEXP_ALLOC_FAIL "An unexpected allocation failed"
# define UNEXP_ALLOC_SUCC "An allocation succeeded where it should have failed"

bool	test_simple_malloc(int log_level);
bool	test_fail_first_malloc(int log_level);
bool	test_fail_third_malloc(int log_level);
bool	test_simple_calloc(int log_level);
bool	test_fail_fifth_calloc(int log_level);

#endif
