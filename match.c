/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:49:34 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 22:50:28 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	call_func(t_str ori, t_str next, t_token_func *fn, t_descriptor *d)
{
	if (fn->token.type == TOKEN_SINGLE_CHAR)
		*d = (*fn->as_char_token)(ori, next, fn->token.as_single_char.chr);
	else if (fn->token.type == TOKEN_STRING)
		*d = (*fn->as_str_token)(ori, next, fn->token.as_string.str);
	else
		*d = (*fn->as_std_token)(ori, next);
}

static void	handle_error(t_str next, t_str str, t_descriptor *d, t_match *mtc)
{
	mtc->has_matched = 0;
	d->error_index = next - str;
	if (*d->end == '\0')
	{
		d->error_index -= 1;
		d->type = TOKEN_INVALID;
	}
}

t_match	parser_match(t_parser *parser, t_str str)
{
	t_match			ret;
	unsigned int	i;
	char			*next;

	i = 0;
	next = str;
	while (i < parser->nbr_fn)
	{
		ret.descs[i].status = DESC_STATUS_NOT_FOUND;
		call_func(str, next, &parser->funcs[i], &ret.descs[i]);
		if (ret.descs[i].status == DESC_STATUS_NOT_FOUND)
		{
			handle_error(next, str, &ret.descs[i], &ret);
			ret.descs[i + 1].type = TOKEN_FINISH_TASK;
			return (ret);
		}
		next = ret.descs[i++].end;
	}
	ret.has_matched = 1;
	ret.descs[i].type = TOKEN_FINISH_TASK;
	return (ret);
}
