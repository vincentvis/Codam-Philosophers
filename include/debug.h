/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debug.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 19:49:55 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/13 15:41:09 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "datastructures.h"

enum e_dprintf_file_actions {
	GET_FD,
	SET_FD,
	CLOSE_FD
};

enum e_asprintf_actions {
	GET_PTR,
	FREE_PTR
};

int		dprintf_file(enum e_dprintf_file_actions action, const char *path);
int		dprintf_wrap_file(const char *str, ...);
int		asprintf_wrap(const char *str, ...);
char	**asprintf_char_ptr(enum e_asprintf_actions action);

int		output_to_stderr(const char *str, ...);
void	output_initialization_info(t_philo_setup setup_values,
			int (*output)(const char *str, ...));

#endif
