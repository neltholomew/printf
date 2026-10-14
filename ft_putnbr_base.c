/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcellar <pcellar@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 15:06:00 by pcellar           #+#    #+#             */
/*   Updated: 2026/09/30 15:50:09 by pcellar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long n, char *base, int *count)
{
	if (n >= ft_strlen(base))
	{
		ft_putnbr_base(n / ft_strlen(base), base, count);
		ft_putnbr_base(n % ft_strlen(base), base, count);
	}
	else
		ft_putchar(base[n], count);
}
