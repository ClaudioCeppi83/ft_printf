/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 20:14:39 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/24 17:48:21 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdbool.h>

void	ft_itoa (t_data *data, union_int int_value)
{
	union_int	tmp;
	//check the base
	if (data->format.base < 2 || data->format.base > 16)
		return ;
	
	//RECURSION check if negative
	if (data->format.is_negative && !data->format.is_converted)
	{
		//inversion
		int_value.int64 = -(int_value.int64);
		data->format.is_converted = true;
		ft_itoa(data, int_value);
	}
	
	//base case
	else if (int_value.uint64 < data->format.base)
	{
		//xX
		if (data->format.upper_case)
			data->format.buffer_temp[data->format.nbr_len++] = UP_SYMBOLS[int_value.uint64];
		else if (data->format.upper_case)
			data->format.buffer_temp[data->format.nbr_len++] = LOW_SYMBOLS[int_value.uint64];
	}
	else
	{
		tmp.uint64 = int_value.uint64 / data->format.base;
		ft_itoa(data, tmp);
		tmp.uint64 = int_value.uint64 % data->format.base;
		ft_itoa(data, tmp);
	}
}