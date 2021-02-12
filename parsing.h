/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:30:28 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/12 17:52:50 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdarg.h>
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

typedef enum e_token_t {
	TOKEN_WHITESPACE,
	TOKEN_WHITESPACES_ZERO_OR_MORE,
	TOKEN_WHITESPACES_ONE_OR_MORE,
	TOKEN_WHITESPACE_NL_ZERO_OR_MORE,
	TOKEN_WHITESPACES_NL_ONE_OR_MORE,
	TOKEN_IDENTIFIER,
	TOKEN_SINGLE_CHAR,
	TOKEN_NUMBER,
	TOKEN_ALNUM_CHAIN,
	TOKEN_SEPARATED,
	TOKEN_END_OF_STREAM,
	TOKEN_FINISH_CREATION,
}	t_token_type;

typedef t_token_type	t_tp;

typedef struct s_token {
	t_token_type	type;
	union {
		struct s_sep {
			t_str			separator;
			t_token_type	in_between;
			unsigned int	nbr;
			unsigned char	accept_whitespace;
		}	as_separated;
		struct s_sc {
			char	chr;
		}	as_single_char;
	};
}	t_token;

typedef struct s_token_func {
	t_token_type	type;
	union {
		t_descriptor (*as_std_token)(t_str str);
		t_descriptor (*as_char_token)(t_str str, char c);
		t_descriptor (*as_sep_token)(t_str str, struct s_sep sep);
	};
}	t_token_func;

typedef struct s_parser {
	unsigned char	is_valid;
	unsigned int	nbr_fn;
	t_token_func	funcs[64];
}	t_parser;

t_token	separator(t_str sep, unsigned int nb, unsigned char ws, t_token_type ib)
{
	return (t_token){
		.type = TOKEN_SEPARATED,
		.as_separated.nbr = nb,
		.as_separated.separator = sep,
		.as_separated.in_between = ib,
		.as_separated.accept_whitespace = ws
	};
}

t_token	token(t_token_type type)
{
	return (t_token){
		.type = type
	};
}

t_token	single_char(char chr)
{
	return (t_token){
		.type = TOKEN_SINGLE_CHAR,
		.as_single_char.chr = chr
	};
}

t_token_func	create_function_pointer(t_token tk)
{
	t_token_func	fn;

	fn.type = tk.type;
	if (tk.type == TOKEN_IDENTIFIER)
		fn.as_std_token = &fn_identifier;
	return (fn);
}

void	parser_create(t_parser *parser, ...)
{
	va_list	args;
	t_token	tk;

	va_start(args, parser);
	parser->is_valid = 0;
	parser->nbr_fn = 0;
	while (1)
	{
		tk = va_arg(args, t_token);
		if (tk.type == TOKEN_FINISH_CREATION)
			break ;
		parser->funcs[parser->nbr_fn++] = create_function_pointer(tk);
	}
	parser->is_valid = 1;
}

void	parser_match(t_parser *parser, t_str str)
{
	t_descriptor	desc;

	desc = (*parser->funcs[0].as_std_token)(str);
	if (desc.status == DESC_STATUS_NOT_FOUND)
	{
		desc.error_index = 1;
		printf(C_RED "Error:\n" C_NRM "%s" C_WHT "\n\n", desc.description);
		printf(C_NRM "%.*s" C_YEL "%.1s" C_NRM "%s\n",
				desc.error_index,
				str + desc.error_index,
				str + desc.error_index,
				str + desc.error_index + 1);
		printf(C_YEL "%*s\n", desc.error_index, "^");
		printf("%*s\n" C_NRM, desc.error_index, "HERE");
	}
}

#endif
