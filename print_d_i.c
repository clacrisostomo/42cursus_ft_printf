/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csantos- <csantos-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 23:52:18 by csantos-          #+#    #+#             */
/*   Updated: 2021/04/15 22:54:55 by csantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Prints decimal and int
*/

static void		verify_d_i(t_flags *flags, long int num)
{
	if (flags->dot == 1)
	{
		flags->zero = 0;
		flags->padding = ' ';
	}
	if (num == INT_MIN)
	{
		num = 2147483648;
		flags->negative = 1;
	}
	if (num < 0)
	{
		flags->negative = 1;
		num = num * (-1);
	}
}

void			print_d_i(t_flags *flags, long int num)
{
	int		size;
	char	*number;

	flags->count++;
	verify_d_i(flags, num);
	number = ft_itoa(num);
	size = (int)ft_strlen(number);
	if (num == 0 && flags->dot == 1)
		size = 0;
	if (flags->negative == 1)
	{
		size = size + 1;
		flags->precision = flags->precision + 1;
	}
	if (flags->negative == 1 && flags->zero == 1)
	{
		ft_putchar(flags, '-');
		print_doido_da_nat(flags, number, size);
	}
	else if (flags->negative == 1 && flags->zero == 0)
		print_doido_da_nat(flags, number, size);
	else
		print_doido_da_cla(flags, number, size);
	free(number);
}

/*
** Deals with precision for d and i
*/

static void		precision_da_nat(t_flags *flags, int size)
{
	ft_putchar(flags, '-');
	if (flags->dot == 1 && flags->precision > size)
	{
		flags->padding = '0';
		print_padding(flags, flags->precision - size);
	}
}

void			print_doido_da_nat(t_flags *flags, char *number, int size)
{
	if (flags->width <= 0)
		flags->width = size;
	else if (flags->width > size && flags->minus == 0)
	{
		if (flags->precision > size)
			flags->width = flags->width - flags->precision;
		else
			flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	if (flags->zero == 0)
		precision_da_nat(flags, size);
	ft_putstr(flags, number, size - 1);
	if (flags->width > size && flags->minus == 1)
	{
		flags->padding = ' ';
		if (flags->precision > size)
			flags->width = flags->width - flags->precision;
		else
			flags->width = flags->width - size;
		print_padding(flags, flags->width);
	}
	reset_da_cla(flags);
}