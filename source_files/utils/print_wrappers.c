/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_wrappers.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/13 14:07:57 by vvissche      #+#    #+#                 */
/*   Updated: 2022/08/15 13:14:25 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdarg.h>
#include "debug.h"

static int	dprintf_open_file(const char *path)
{
	int	fd;

	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd < 0)
		return (-1);
	return (fd);
}

char	**asprintf_char_ptr(enum e_asprintf_actions action)
{
	(void)action;
	return (NULL);
}

int	asprintf_wrap(const char *str, ...)
{
	(void)str;
	return (0);
}

int	dprintf_file(enum e_dprintf_file_actions action, const char *path)
{
	(void)action;
	(void)path;
	return (0);
	dprintf_open_file("");
}

int	dprintf_wrap_file(const char *str, ...)
{
	(void)str;
	return (0);
}

/*

These are not allowed functions, so they are commented out for now..

int	dprintf_file(enum e_dprintf_file_actions action, const char *path)
{
	static int	fd = 0;

	if (action == CLOSE_FD)
		fd = close(fd);
	if (action == SET_FD && path)
	{
		if (fd > 0)
			close(fd);
		fd = dprintf_open_file(path);
	}
	return (fd);
}

int	dprintf_wrap_file(const char *str, ...)
{
	const int	fd = dprintf_file(GET_FD, NULL);
	va_list		ap;
	int			n;

	if (fd <= 0)
		return (-1);
	va_start(ap, str);
	n = vdprintf(fd, str, ap);
	va_end(ap);
	return (n);
}

char	**asprintf_char_ptr(enum e_asprintf_actions action)
{
	static char	*ptr;

	if (action == FREE_PTR)
	{
		free(ptr);
		ptr = NULL;
	}
	return (&ptr);
}

*/

/*
	example use:

	// call function with asprintf_wrap as printing function
	output_initialization_info(setup_values, asprintf_wrap);

	// get char from singleton
	char **asprintf_result = asprintf_char_ptr(GET_PTR);
	// test result
	if (memcmp(expected, *asprintf_result, expected_length) == 0))
		return (true);
	else
		return (false);
	// free result
	asprintf_char_ptr(FREE_PTR);
*/

/*

int	asprintf_wrap(const char *str, ...)
{
	char		**dst;
	va_list		ap;
	int			n;

	dst = asprintf_char_ptr(GET_PTR);
	va_start(ap, str);
	n = vasprintf(dst, str, ap);
	va_end(ap);
	return (n);
}

*/
