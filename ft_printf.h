/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:42:58 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/20 22:00:48 by cceppi-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF
# define FT_PRINTF

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <limits.h>

/* (1<<12) es equivalente a 4096, resulta mas 
practico al cambiar el tamano de la memoria */
#define BUF_SIZE (1<<12)

//********** STRINGS **********

#define FLAGS "[0-' '#+]"
#define WITDH "0123456789"
#define SPECIFIERS "csdixXpu"

//*********** BASES ***********

typedef enum
{
	BASE_2 = 2,
	BASE_8 = 8,
	BASE_10 = 10,
	BASE_16 = 16,
} e_base;

//********** STRUCTS **********

typedef struct s_format
{
	//FLAGS
	bool	left_justified;
	bool	plus;
	bool	space;
	bool	hash;
	bool	zero_pad;

	//"csdixXpu..."
	char	specifier;

	//width and precision
	int	with_value;
	int	precision_value;

	//utils
	bool	upper_case;
	e_base	base;

} t_format;

typedef struct s_data
{
	//pointer copy
	const char	*s;
	//lists
	va_list	ap;
	//chars counter
	int	char_count;
	//buffer
	char	*buffer;
	int	buffer_index;

	//FLAGS, specifiers, width and precision
	t_format	format;

} t_data;

//******** ERROR ALIAS ********

typedef enum
{
	OK = 0,
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
} e_error;

//******** PROTOTYPES *********

//Utils
void	*ft_memset(void *b, int c, size_t len);
bool	in(const char *s, char c);

//Parser
int	parse_format(t_data *data);


#endif