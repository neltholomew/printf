/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcellar <pcellar@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 16:44:32 by pcellar           #+#    #+#             */
/*   Updated: 2026/09/30 13:01:11 by pcellar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	if (n == -2147483648)
	{
		ft_putchar('-', count);
		ft_putchar('2', count);
		ft_putnbr(147483648, count);
	}
	else if (n < 0)
	{
		ft_putchar('-', count);
		ft_putnbr(-n, count);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10, count);
		ft_putnbr(n % 10, count);
	}
	else
	{
		ft_putchar(n + '0', count);
	}
}
