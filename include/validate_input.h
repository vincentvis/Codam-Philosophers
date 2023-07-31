/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   validate_input.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:14:44 by vvissche      #+#    #+#                 */
/*   Updated: 2022/04/19 16:23:46 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_INPUT_H
# define VALIDATE_INPUT_H

# include "datastructures.h"

int	parse_philosopher_program_input(t_philo_setup *setup_values,
		int argc, char const *argv[]);

#endif
