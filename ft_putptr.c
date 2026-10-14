/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcellar <pcellar@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 15:53:18 by pcellar           #+#    #+#             */
/*   Updated: 2026/09/30 16:01:12 by pcellar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr(void *ptr, int *count)
{
	if (ptr == NULL)
	{
		(*count) += write (1, "(nil)", 5);
		return ;
	}
	ft_putstr("0x", count);
	ft_putnbr_base((unsigned long)ptr, "0123456789abcdef", count);
}
