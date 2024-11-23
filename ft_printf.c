/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:39:39 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/23 20:04:33 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_printf.h"
#include <stdarg.h>

void	render_format(t_data *data)
{
	char	specifier;
	union_int	int_values;

	specifier = data->format.specifier;
	int_values.int64 = 0;
	if ('%' == specifier)
		print_char(data, '%');
	else if ('c' == specifier)
		print_char(data, va_arg(data->ap, int));
	else if ('s' == specifier)
		print_str(data, va_arg(data->ap, char *));
	if (in("dixXpu", specifier))
	{
		if (in("di", specifier))
		{
			int_values.int64 = (long)va_arg(data->ap, int);
			data->format.signed_value = true;
				if (int_values.int64 < 0)
					data->format.is_negative = true;
		}
		else if (in("p", specifier))
			int_values.uint64 = (unsigned long)va_arg(data->ap, void *);
		else if (in("xXu", specifier))
			int_values.uint64 = (unsigned long)va_arg(data->ap, unsigned int);
	}
}

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
		return MALLOC_ERROR;
	
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