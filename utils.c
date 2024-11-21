/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:02:59 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/21 19:55:50 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdbool.h>

void	*ft_memset(void *b, byte c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len > 0)
	{
		*temp = c;
		temp++;
		len--;
	}
	return (b);
}

bool	in(const char *s, char c)
{
	if (NULL == s)
		return false;
	while (*s)
	{
		if (*s == c)
			return true;
		++s;
	}
	return false;
}

int	ft_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (in(WITDH, *data->s))
		value = (value * 10) + (*data->s++ - '0');
	return (value);
}

void get_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return;
	}
	*value = ft_atoi(data);
}