/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:02:35 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/24 20:16:56 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_int(t_data *data, union_int int_value)
{
	//int to str
	ft_itoa(data, int_value);
	padding_zeros(data);
	padding_spaces(data);
	if (data->format.left_justified)
	{
		//1
		put_sign(data);
		//2
		putchar_buffer_n('0', data->format.padding_zeros, data);
		//3
		putstr_buffer_n(data->format.buffer_temp, data->format.nbr_len, data);
		//4
		putchar_buffer_n(' ', data->format.padding_spaces, data);
	}
	else
	{
		//1
		putchar_buffer_n(' ', data->format.padding_spaces, data);
		//2
		put_sign(data);
		//3
		putchar_buffer_n('0', data->format.padding_zeros, data);
		//4
		putstr_buffer_n(data->format.buffer_temp, data->format.nbr_len, data);
	}
}