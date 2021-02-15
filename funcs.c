/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:48:00 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 18:44:31 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "funcs.h"
#include <stdlib.h>

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
		ret.end = ++str;
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
