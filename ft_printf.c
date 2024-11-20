/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:39:39 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/20 22:01:38 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <stdarg.h>

static int	init_data(t_data *data, const char *format)
{
	data->char_count = 0;
	data->s = format;
	data->buffer = malloc(BUF_SIZE * sizeof(char));
	if (NULL == data->buffer)
		return MALLOC_ERROR;
	data->buffer_index = 0;
	ft_memset(data->buffer, 0, BUF_SIZE * sizeof(char));
	return OK;
}

int	ft_printf(const char *format, ...)
{
	t_data	data;

	//starting the variadic functions and data
	va_start(data.ap, format);
	if (init_data(&data, format))
		return -1;
	
	//starting the function
	while (*data.s)
	{
		if (*data.s == '%' && *(++data.s))
		{
			if (parse_format(&data))
				return PARSE_ERROR;
			render_format(&data);
		}
		else
		{
			// data.buffer[data.buffer_index++] = *data.s;
			write_buffer(&data, *data.s);
		}
		++data.s;
	}
	flush_buffer(&data);
	va_end(data.ap);
	free(data.buffer);
	return (data.char_count);
}