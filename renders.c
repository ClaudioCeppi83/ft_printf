/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:07:10 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/23 18:37:05 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	set_str_spaces(t_data *data, char *s)
{
	int	len;

	len = ft_strlen(s);
	if (data->format.with_value > 0)
	{
		if (data->format.precision_value >= 0)
		{
			if (data->format.precision_value > len)
			{
				
			}
			else if (data->format.precision_value < len)
			{
				data->format.padding_spaces = data->format.with_value - \
												data->format.padding_spaces;
			}
		}
		else
		{
			data->format.padding_spaces = data->format.with_value - len;
		}
	}
}

void	render_format(t_data *data)
{
	char	specifier;

	specifier = data->format.specifier;
	if ('%' == specifier)
		print_char(data, '%');
	else if ('c' == specifier)
		print_char(data, va_arg(data->ap, int));
	else if ('s' == specifier)
		print_str(data, va_arg(data->ap, char *));
}

void	print_char(t_data *data, int c)
{
	int	witdh;

	witdh = data->format.with_value;
	if (witdh > 1)
	{
		if (data->format.left_justified)
		{
			//adding spaces right
			putchar_buffer_n((char)c, 1, data);
			putchar_buffer_n(' ', witdh - 1, data);
		}
		else
		{
			//adding spaces left
			putchar_buffer_n(' ', witdh - 1, data);
			putchar_buffer_n((char)c, 1, data);
		}
	}
	else
		putchar_buffer_n((char)c, 1, data);
}

void	print_str(t_data *data, char *s)
{
	if (NULL == s)
		s = "(null)";
	set_str_spaces(data, s);
	if (data->format.left_justified)
	{
		if (data->format.precision_value >= 0)
			putstr_buffer_n(s, data->format.precision_value, data);
		else
			putstr_buffer_n(s, ft_strlen(s), data);
		putchar_buffer_n(' ', data->format.padding_spaces, data);
	}
	else
	{
		putchar_buffer_n(' ', data->format.padding_spaces, data);
		if (data->format.precision_value >= 0)
			putstr_buffer_n(s, data->format.precision_value, data);
		else
			putstr_buffer_n(s, ft_strlen(s), data);
	}
}