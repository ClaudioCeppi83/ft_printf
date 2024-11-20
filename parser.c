/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 22:02:39 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/20 22:02:43 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "utils.c"

static void	parse_flags(t_data *data)
{
	char	flag;

	while (in(FLAGS, *data->s))
	{
		flag = *data->s;
		if ('0' == flag)
			data->format.zero_pad = true;
		else if ('+' == flag)
			data->format.plus = true;
		else if (' ' == flag)
			data->format.space = true;
		else if ('#' == flag)
			data->format.hash = true;
		else if ('-' == flag)
			data->format.left_justified = true;
		++data->s;
	}
}

//flags: %[0-' '#+][witdh][.precision]d"
int parse_format(t_data *data)
{
	// data refresh
	ft_memset(&data->format, 0, sizeof(t_format));
	data->format.precision_value = -1;

	//parsing [0-' '#+]
	parse_flags(data);

	//parsing [witdh *]
	get_value(data, &data->format.with_value);

	//parsing [.precision]
	if (*data->s == '.' && *(++data->s))
		get_value(data, &data->format.precision_value);

	//parsing [dipxX..]
	if (!in(SPECIFIERS, *data->s))
		return PARSE_ERROR;
	else
	{
		data->format.specifier = *data->s;

		//BASES
		if (in("diu", data->format.specifier))
			data->format.base = BASE_10;
		else if (in("xXp", data->format.specifier))
		{
			data->format.base = BASE_16;
			if ('X' == data->format.specifier)
				data->format.upper_case = true;
		}

		//...octal, binary
	}
	return OK;
}