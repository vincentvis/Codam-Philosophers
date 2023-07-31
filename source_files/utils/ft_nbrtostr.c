/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrtostr.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/06 08:57:57 by vvissche      #+#    #+#                 */
/*   Updated: 2022/07/22 17:03:55 by vvissche      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>

static const int16_t	*get_base10_short(void)
{
	static int16_t	*base = (int16_t *)"00010203040506070809"
		"10111213141516171819"
		"20212223242526272829"
		"30313233343536373839"
		"40414243444546474849"
		"50515253545556575859"
		"60616263646566676869"
		"70717273747576777879"
		"80818283848586878889"
		"90919293949596979899";

	return (base);
}

int32_t	ft_nbrlen_u(uint64_t value)
{
	if (value < 10)
		return (1);
	if (value < 100)
		return (2);
	if (value < 1000)
		return (3);
	if (value < 10000)
		return (4);
	if (value < 100000)
		return (5);
	if (value < 1000000)
		return (6);
	if (value < 10000000)
		return (7);
	if (value < 100000000)
		return (8);
	if (value < 1000000000)
		return (9);
	if (value < 10000000000)
		return (10);
	if (value < 100000000000)
		return (11);
	if (value < 1000000000000)
		return (12);
	return (12 + ft_nbrlen_u(value / 1000000000000));
}

int	ft_nbrtostr_n(char *dst, uint64_t nbr, uint32_t nbrlen)
{
	const int16_t	*base10 = get_base10_short();
	uint64_t		division;

	dst[0] = '0';
	dst[nbrlen] = 0;
	division = nbr;
	if (nbr != 0)
		dst += nbrlen;
	while (division >= 100)
	{
		dst -= 2;
		division = division / 100;
		*(int16_t *)dst = base10[nbr - (100 * division)];
		nbr = division;
	}
	while (division > 0)
	{
		dst--;
		division = division / 10;
		*dst = (char)(nbr - (10 * division)) + '0';
		nbr = division;
	}
	return (nbrlen);
}
