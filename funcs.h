/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:47:26 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 17:44:06 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

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
	TOKEN_SEPARATED,
	TOKEN_END_OF_STREAM,
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
	t_str			err_desc;
	t_desc_status	status;
	unsigned int	error_index;
}	t_descriptor;

t_descriptor	fn_identifier(t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_IDENTIFIER;
	ret.start = str;
	ret.end = str;
	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| *str == '_')
		ret.end = ++str;
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		ret.err_desc = "'IDENTIFIER': expected "
			"alphabetical character or underscore";
		ret.error_index = 0;
		return (ret);
	}
	while ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| *str == '_' || (*str >= '0' && *str <= '9'))
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_number(t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_NUMBER;
	ret.start = str;
	ret.end = str;
	if (*str >= '0' && *str <= '9')
	{
		ret.start = str;
		ret.end = ++str;
	}
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		ret.err_desc = "'NUMBER': expected "
			"numerical character";
		ret.error_index = 0;
		return (ret);
	}
	while (*str && *str >= '0' && *str <= '9')
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_ws1(t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_WHITESPACES_ONE_OR_MORE;
	ret.start = str;
	ret.end = str;
	if (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
	{
		ret.start = str;
		ret.end = ++str;
	}
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		ret.err_desc = "'WHITESPACES_ONE_OR_MORE': expected "
			"whitespace character (ascii 0x9 -> 0xd, space)";
		ret.error_index = 0;
		return (ret);
	}
	while (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_ws0(t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_WHITESPACES_ZERO_OR_MORE;
	ret.start = str;
	ret.end = str;
	while (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_char(t_str str, char c)
{
	t_descriptor	ret;
	unsigned int	i;

	ret.type = TOKEN_SINGLE_CHAR;
	ret.start = str;
	ret.end = str;
	if (*str == c)
	{
		ret.start = str;
		ret.end = ++str;
	}
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		ret.err_desc = malloc(46);
		i = 0;
		while (("SINGLE_CHAR: expected character '?', got '?'")[i])
		{
			ret.err_desc[i]
				= ("SINGLE_CHAR: expected character '?', got '?'")[i];
			++i;
		}
		ret.err_desc[33] = c;
		ret.err_desc[42] = *str;
		ret.err_desc[i] = 0;
	}
	return (ret);
}

#endif
