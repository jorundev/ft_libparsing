/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:34:23 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/19 14:21:59 by kryckely         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "funcs.h"
#include <stdio.h>

t_descriptor	fn_str(t_str ori, t_str str, t_str str2)
{
	t_descriptor	ret;
	unsigned int	i;

	ret.start = str;
	ret.end = str;
	i = 0;
	while (str2[i])
	{
		if (str[i] != str2[i])
		{
			ret.status = DESC_STATUS_NOT_FOUND;
			printf(C_RED "Error:\n" C_NRM "'STRING': expected '%c', got '%c'"
			C_WHT "\n\n", str2[i], str[i]);
			ret.error_index = str - ori + i;
			display_desc_error(&ret, ori);
			return (ret);
		}
		++i;
		++ret.end;
	}
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_not_ws_seq(t_str ori, t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_NOT_WS_SEQ;
	ret.start = str;
	ret.end = str;
	if (*str && !(*str == 0x9 || (*str >= 0xa && *str <= 0xd) || *str == 0x20))
	{
		ret.start = str;
		ret.end = ++str;
	}
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		printf(C_RED "Error:\n" C_NRM "'NOT_WS_SEQ': "
		"expected not whitespace, got '%c' (%#2.2x)"
		C_WHT "\n\n", *str, *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		return (ret);
	}
	while (*str && !(*str == 0x9 || (*str > 0x9 && *str < 0xe) || *str == 0x20))
		ret.end = ++str;
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_ws(t_str ori, t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_WHITESPACE;
	ret.start = str;
	ret.end = str;
	if (*str == 0x9 || (*str >= 0xb && *str <= 0xd) || *str == 0x20)
		ret.end = ++str;
	else
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		printf(C_RED "Error:\n" C_NRM "'WHITESPACE': "
		"expected whitespace, got '%c'"
		C_WHT "\n\n", *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		ret.error_index = 0;
		return (ret);
	}
	ret.status = DESC_STATUS_OK;
	return (ret);
}

t_descriptor	fn_end(t_str ori, t_str str)
{
	t_descriptor	ret;

	ret.type = TOKEN_END_OF_STREAM;
	ret.start = str;
	ret.end = str;
	if (*str != '\0')
	{
		ret.status = DESC_STATUS_NOT_FOUND;
		printf(C_RED "Error:\n" C_NRM "'END_OF_STREAM': expected 'EOF', got '%c'"
		C_WHT "\n\n", *str);
		ret.error_index = str - ori;
		display_desc_error(&ret, ori);
		ret.error_index = 0;
		return (ret);
	}
	ret.status = DESC_STATUS_OK;
	return (ret);
}
