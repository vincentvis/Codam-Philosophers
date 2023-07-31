/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   forks.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 16:55:35 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/12 11:59:14 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORKS_H
# define FORKS_H

# include <pthread.h>
# include <stdint.h>

int32_t	create_fork(pthread_mutex_t **mutex);
int32_t	destroy_fork(pthread_mutex_t **mutex);
int32_t	create_forks(
			pthread_mutex_t ***fork_array,
			const int32_t num_philosophers);
void	*destroy_forks(pthread_mutex_t **fork_array);
void	assign_forks_to_philosopher(
			t_philo	*philosopher,
			t_philo_setup setup_values);

#endif
