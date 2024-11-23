/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:40:10 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/23 17:54:56 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void	flush_buffer(t_data *data)
{
	//write
	data->char_count += write(STDOUT_FILENO, data->buffer, data->buffer_index);

	//refresh after call
	ft_memset(data->buffer, 0, BUF_SIZE);
	data->buffer_index = 0;
}

void	write_buffer(t_data *data, char c)
{
	if (data->buffer_index == BUF_SIZE)
		//refresh index and write the string
		flush_buffer(data);
	data->buffer[data->buffer_index++] = c;
}

void	putchar_buffer_n(char c, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision--)
		write_buffer(data, c);
}

void	putstr_buffer_n(char *s, int precision, t_data *data)
{
	if (precision <= 0)
		return ;
	while (precision-- && *s)
		write_buffer(data, *s++);
}