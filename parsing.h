/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:30:28 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/19 09:34:32 by kryckely         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include "funcs.h"

typedef char*			t_str;
typedef unsigned char	t_u8;
typedef unsigned int	t_u32;

# define	C_NRM	"\x1B[0m"
# define	C_RED	"\x1B[31m"
# define	C_GRN	"\x1B[32m"
# define	C_YEL	"\x1B[33m"
# define	C_BLU	"\x1B[34m"
# define	C_MAG	"\x1B[35m"
# define	C_CYN	"\x1B[36m"
# define	C_WHT	"\x1B[37m"

typedef t_token_type	t_tp;

t_u8					g_stop_parsing_log;

typedef struct s_token {
	t_token_type	type;
	union {
		struct s_tk_str {
			t_str			str;
		}	as_string;
		struct s_sc {
			char	chr;
		}	as_single_char;
	};
}	t_token;

typedef struct s_token_func {
	t_token		token;
	union {
		t_descriptor	(*as_std_token)(t_str ori, t_str str);
		t_descriptor	(*as_str_token)(t_str ori, t_str str, t_str str2);
		t_descriptor	(*as_char_token)(t_str ori, t_str str, char c);
	};
}	t_token_func;

typedef struct s_parser {
	unsigned char	is_valid;
	unsigned int	nbr_fn;
	t_token_func	funcs[64];
}	t_parser;

typedef struct s_match {
	t_descriptor	descs[64];
	t_u8			has_matched;
}	t_match;

t_token			token_string(t_str str);

t_token			token(t_token_type type);

t_token			token_char(char chr);

t_token_func	create_function_pointer(t_token tk);

void			parser_create(t_parser *parser, ...);

void			print_spaces(t_descriptor *desc, t_str str);

t_match			parser_match(t_parser *parser, t_str str);

t_str			desc_as_str(t_descriptor *desc);

#endif
