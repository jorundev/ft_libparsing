/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:47:26 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/19 11:27:56 by kryckely         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

# include <stdio.h>

# define	C_NRM	"\x1B[0m"
# define	C_RED	"\x1B[31m"
# define	C_GRN	"\x1B[32m"
# define	C_YEL	"\x1B[33m"
# define	C_BLU	"\x1B[34m"
# define	C_MAG	"\x1B[35m"
# define	C_CYN	"\x1B[36m"
# define	C_WHT	"\x1B[37m"

typedef char*			t_str;

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
	TOKEN_END_OF_STREAM,
	TOKEN_STRING,
	TOKEN_NOT_WS_SEQ,
	TOKEN_INVALID,
	TOKEN_FINISH_TASK,
}	t_token_type;

typedef enum e_descstat {
	DESC_STATUS_LAST,
	DESC_STATUS_OK,
	DESC_STATUS_NOT_FOUND
}	t_desc_status;

typedef struct s_descriptor {
	char			*start;
	char			*end;
	t_token_type	type;
	t_desc_status	status;
	unsigned int	error_index;
}	t_descriptor;

t_descriptor	fn_identifier(t_str ori, t_str str);

t_descriptor	fn_number(t_str ori, t_str str);

t_descriptor	fn_ws(t_str ori, t_str str);

t_descriptor	fn_ws1(t_str ori, t_str str);

t_descriptor	fn_ws0(t_str ori, t_str str);

t_descriptor	fn_char(t_str ori, t_str str, char c);

t_descriptor	fn_str(t_str ori, t_str str, t_str str2);

t_descriptor	fn_not_ws_seq(t_str ori, t_str str);

t_descriptor	fn_end(t_str ori, t_str str);

void			display_desc_error(t_descriptor *desc, t_str str);

#endif
