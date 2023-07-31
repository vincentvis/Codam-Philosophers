/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   strtoll.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvissche <vvissche@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/05 10:06:05 by vvissche      #+#    #+#                 */
/*   Updated: 2022/06/13 16:49:39 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "strtoll.h"

static const t_basemap	*get_basemap(void)
{
	static const t_basemap	basemap[127] = {
	['0'] = {.base = 2, .value = 0},
	['1'] = {.base = 2, .value = 1},
	['2'] = {.base = 3, .value = 2},
	['3'] = {.base = 4, .value = 3},
	['4'] = {.base = 5, .value = 4},
	['5'] = {.base = 6, .value = 5},
	['6'] = {.base = 7, .value = 6},
	['7'] = {.base = 8, .value = 7},
	['8'] = {.base = 9, .value = 8},
	['9'] = {.base = 10, .value = 9}
	};

	return (basemap);
}

static uint_fast8_t	ft_strtoll_setup(int *base, unsigned long long *sign,
									const char **str, char **endptr)
{
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '-')
		*sign = IS_NEGATIVE;
	if (**str == '-' || **str == '+')
		(*str)++;
	if (*base < 0 || *base == 1 || *base > 36)
		return (0);
	if (**str == '0')
	{
		if ((*base == 0 || *base == 16)
			&& ((*str)[1] == 'x' || (*str)[1] == 'X'))
		{
			(*str) += 2;
			*base = 16;
		}
		else if (*base == 0)
			*base = 8;
	}
	else if (*base == 0)
		*base = 10;
	if (endptr)
		*endptr = (char *)*str;
	return (1);
}

static char	*ft_strtoll_start(char **endptr,
						const char *str,
						unsigned long long *n)
{
	errno = 0;
	if (endptr)
		*endptr = (char *)str;
	n[3] = IS_POSITIVE;
	n[4] = 0;
	n[0] = 0;
	n[1] = LONG_MAX / 10;
	n[2] = LONG_MAX % 10;
	return ((char *)str);
}

/*
** If no conversion has taken place and there is an endptr
** we still need to set it properly
** there is an edgecase, for base 0/16 and the first 2 chars are 0 and x/X
** but the rest is not hexadecimal
** then we return the pointer to the x/X and return 0
*/

static long long	ft_strtoll_return(int action, char **endptr, char *save,
		unsigned long long n[5])
{
	if (action == ACTION_NOCONV)
	{
		if (endptr)
		{
			if (*endptr - save >= 2
				&& ((*endptr)[-1] == 'x' || (*endptr)[-1] == 'X')
				&& (*endptr)[-2] == '0')
				*endptr = &((*endptr)[-1]);
			else
				*endptr = save;
		}
		return (0LL);
	}
	if (n[4] == HAS_OVERFLOW)
	{
		errno = ERANGE;
		if (n[3] == IS_NEGATIVE)
			return (LONG_MIN);
		return (LONG_MAX);
	}
	if (n[3] == IS_NEGATIVE)
		return (-((long long)n[0]));
	return ((long long)n[0]);
}

/*
** n[0] = number we are trying to get from the string
** n[1] = g_max = max value for base
** n[2] = g_rem = modulus for base
** n[3] = sign
** n[4] = overflow
*/

long long	ft_strtoll(const char *str,
				char **endptr,
				int base)
{
	char				*save;
	unsigned long long	n[5];
	t_basemap			num;
	const t_basemap		*basemap = get_basemap();

	save = ft_strtoll_start(endptr, str, n);
	if (!ft_strtoll_setup(&base, &n[3], &str, endptr))
		return (0LL);
	num = basemap[(int)*str];
	if (!(num.base <= base && num.base))
		return (ft_strtoll_return(ACTION_NOCONV, endptr, save, n));
	while (num.base <= base && num.base)
	{
		if (n[0] > n[1] || (n[0] == n[1] && (uint64_t)num.value > n[2]))
			n[4] = HAS_OVERFLOW;
		n[0] = num.value + (n[0] * base);
		str++;
		num = basemap[(int)*str];
	}
	if (endptr)
		*endptr = (char *)str;
	return (ft_strtoll_return(ACTION_DEFAULT, endptr, save, n));
}
