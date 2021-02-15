/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:49:34 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 19:06:03 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	call_func(t_str next, t_token_func *fn, t_descriptor *desc)
{
	if (fn->token.type == TOKEN_SINGLE_CHAR)
		*desc = (*fn->as_char_token)(next, fn->token.as_single_char.chr);
	else
		*desc = (*fn->as_std_token)(next);
}

static void	free_if_single_char(t_descriptor *desc)
{
	if (desc->type == TOKEN_SINGLE_CHAR)
		free(desc->err_desc);
}

static void	handle_error(t_str next, t_str str, t_descriptor *d, t_match *mtc)
{
	mtc->has_matched = 0;
	d->error_index = next - str;
	if (*d->end == '\0')
	{
		free_if_single_char(d);
		d->error_index -= 1;
		d->err_desc = "Unexpected end of string";
		d->type = TOKEN_INVALID;
	}
	display_desc_error(d, str);
	free_if_single_char(d);
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
		call_func(next, &parser->funcs[i], &ret.descs[i]);
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
