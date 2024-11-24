/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cceppi-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:42:58 by cceppi-c          #+#    #+#             */
/*   Updated: 2024/11/24 20:17:43 by cceppi-c         ###   ########.fr       */
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

typedef unsigned char	byte;

//********** STRINGS **********

#define FLAGS "[0-' '#+]"
#define WITDH "0123456789"
#define SPECIFIERS "csdixXpu%"
#define LOW_SYMBOLS "0123456789abcdef"
#define UP_SYMBOLS "0123456789ABCDEF"

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
	char	buffer_temp[64];
	int	nbr_len;
	bool	upper_case;
	e_base	base;
	int	padding_spaces;
	int	padding_zeros;
	bool	signed_value;
	bool	is_negative;
	bool	is_converted;

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

typedef union
{
	unsigned long	uint64;
	long	int64;
} union_int;

//******** ERROR ALIAS ********

typedef enum
{
	OK = 0,
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
} e_error;

//******** PROTOTYPES *********

//Utils
void	*ft_memset(void *b, byte c, size_t len);
bool	in(const char *s, char c);
int	ft_atoi(t_data *data);
void	ft_itoa (t_data *data, union_int int_value);
void get_value(t_data *data, int *value);
size_t	ft_strlen(const char *str);

//Parser
int	parse_format(t_data *data);

//Buffer
void	write_buffer(t_data *data, char c);
void	flush_buffer(t_data *data);
void	putchar_buffer_n(char c, int precision, t_data *data);
void	putstr_buffer_n(char *s, int precision, t_data *data);

//Render
void	render_format(t_data *data);
void	print_char(t_data *data, int c);
void	print_str(t_data *data, char *s);
void	padding_spaces(t_data *data);
void	padding_zeros(t_data *data);
void	put_sign(t_data *data);
void	print_int(t_data *data, union_int int_value);


#endif