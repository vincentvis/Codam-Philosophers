/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleanup.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/04 18:27:04 by vincent       #+#    #+#                 */
/*   Updated: 2022/08/16 13:45:43 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEANUP_H
# define CLEANUP_H

int32_t	philo_create_fail(
			t_philo *philosopher_threads,
			t_philo_setup *setup_values,
			int32_t index,
			int32_t status);
int		cleanup_after_simulation(t_philo_setup *setup_values);
int32_t	join_philosophers(
			t_philo *philosopher_threads,
			t_philo_setup *setup_values,
			int32_t n_philo);

#endif
