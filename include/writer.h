/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/07/22 14:30:38 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 15:07:12 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITER_H
# define WRITER_H

# include "philosophers.h"
# include "datastructures.h"
# include <stdint.h>

// void	output_philo_status(uint64_t timestamp, int32_t index,
// 			enum e_philosopher_state action);
void	output_philo_status(t_message message);
int32_t	writer_mutex(enum e_singleton_action action);
void	*writer_routine(void *arg);

#endif
