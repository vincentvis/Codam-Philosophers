/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strtoll.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/14 17:28:53 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/13 12:49:06 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRTOLL_H
# define STRTOLL_H

# include <stdint.h>
# include <limits.h>
# include <errno.h>

# define HAS_OVERFLOW 1
# define IS_NEGATIVE 1
# define IS_POSITIVE 0
# define ACTION_NOCONV 1
# define ACTION_DEFAULT 0

typedef struct s_basemap
{
	int	base;
	int	value;
}					t_basemap;

#endif
