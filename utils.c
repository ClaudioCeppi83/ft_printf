/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:02:59 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/20 22:03:02 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdbool.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;

	temp = (unsigned char *)b;
	while (len > 0)
	{
		*temp = (unsigned char)c;
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

static int	ft_atoi(t_data *data)
{
	int	value;

	value = 0;
	while (in(WITDH, *data->s))
		value = (value * 10) + (*data->s++ - '0');
	return (value);
}

static void get_value(t_data *data, int *value)
{
	if (*data->s == '*')
	{
		*value = va_arg(data->ap, int);
		++data->s;
		return;
	}
	*value = ft_atoi(data);
}