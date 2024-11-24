/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:56:03 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/24 20:13:14 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	padding_zeros(t_data *data)
{
	if (data->format.precision_value >= 0)
	{
		if (data->format.precision_value > data->format.nbr_len)
		{
			data->format.padding_zeros = data->format.precision_value - data->format.nbr_len;
			return ;
		}
	}
	if (data->format.zero_pad)
	{
		if (data->format.left_justified)
			return ;
		if (data->format.with_value > data->format.nbr_len)
			data->format.padding_zeros = data->format.with_value - data->format.nbr_len;
		if (data->format.specifier == 'u')
			return ;
		else if ((in("xX", data->format.specifier) && data->format.hash && data->format.buffer_temp[0] != '0') || data->format.specifier == 'p')
			data->format.padding_zeros -= 2;
		else if (data->format.is_negative || (!data->format.is_negative && (data->format.plus || data->format.space)))
			data->format.padding_zeros--;
	}
	if (data->format.padding_zeros < 0)
		data->format.padding_zeros = 0;
}

void	padding_spaces(t_data *data)
{
	data->format.padding_spaces = data->format.with_value - data->format.padding_zeros - data->format.nbr_len;
	if (in("uxXp", data->format.specifier))
	{
		if ((in("xX", data->format.specifier) && data->format.hash && data->format.buffer_temp[0] != '0') || data->format.specifier == 'p')
			data->format.padding_spaces -= 2;
		return ;
	}
	if (data->format.is_negative)
		data->format.padding_spaces--;
	return ;
	if (!data->format.is_negative && data->format.plus)
		data->format.padding_spaces--;
	return ;
	if (!data->format.is_negative && data->format.space)
		data->format.padding_spaces--;
	return ;
}

void	put_sign(t_data *data)
{
	if ((in("xX", data->format.specifier) && data->format.hash && data->format.buffer_temp[0] != '0') || data->format.specifier == 'p')
	{
		if (data->format.upper_case)
			putstr_buffer_n("0X", 2, data);
		else
			putstr_buffer_n("0x", 2, data);
	}
	else if (data->format.signed_value)
	{
		if (data->format.is_negative)
			putchar_buffer_n('-', 1, data);
		else if (!data->format.is_negative)
		{
			if (data->format.plus)
				putchar_buffer_n('+', 1, data);
			else if (!data->format.plus && data->format.space)
				putchar_buffer_n('+', 1, data);
		}
	}
}