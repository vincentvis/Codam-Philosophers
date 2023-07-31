/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_validate_input.h                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/20 14:46:47 by vvissche      #+#    #+#                 */
/*   Updated: 2022/07/26 16:46:52 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_VALIDATE_INPUT_H
# define T_VALIDATE_INPUT_H

bool	test_invalid_value_not_setting_variable(int log_level);
bool	test_negative_value_returning_false(int log_level);
bool	test_non_digit_in_input_returns_false(int log_level);
bool	test_assign_all_five_values(int log_level);
bool	test_long_max_plus_one_errno(int log_level);

#endif
