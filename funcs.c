/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:48:00 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/19 09:35:29 by kryckely         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "funcs.h"
#include <stdlib.h>

t_descriptor	fn_identifier(t_str ori, t_str str)
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
		printf(C_RED "Error:\n" C_NRM "'IDENTIFIER': expected "
		"alphabetical character or underscore, got '%c'"
		C_WHT "\n\n", *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		return (ret);
	}
	while ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| *str == '_' || (*str >= '0' && *str <= '9'))
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_number(t_str ori, t_str str)
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
		printf(C_RED "Error:\n" C_NRM "'NUMBER': expected "
		"numerical character, got '%c'"
		C_WHT "\n\n", *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		ret.error_index = 0;
		return (ret);
	}
	while (*str && *str >= '0' && *str <= '9')
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_ws1(t_str ori, t_str str)
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
		printf(C_RED "Error:\n" C_NRM "'WHITESPACES_ONE_OR_MORE': "
		"expected whitespace, got '%c'"
		C_WHT "\n\n", *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		ret.error_index = 0;
		return (ret);
	}
	while (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_ws0(t_str ori, t_str str)
{
	t_descriptor	ret;

	(void)ori;
	ret.type = TOKEN_WHITESPACES_ZERO_OR_MORE;
	ret.start = str;
	ret.end = str;
	while (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_char(t_str ori, t_str str, char c)
{
	t_descriptor	ret;

	ret.type = TOKEN_SINGLE_CHAR;
	ret.start = str;
	ret.end = str;
	if (*str == c)
		ret.end = ++str;
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		printf(C_RED "Error:\n" C_NRM "'SINGLE_CHAR': expected '%c', got '%c'"
		C_WHT "\n\n", c, *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
	}
	return (ret);
}
