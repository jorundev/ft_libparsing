/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:45:23 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 18:47:38 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	separator(t_str sep, t_u8 nb, t_u8 ws, t_token_type ib)
{
	return (
		(t_token){
		.type = TOKEN_SEPARATED,
		.as_separated.nbr = nb,
		.as_separated.separator = sep,
		.as_separated.in_between = ib,
		.as_separated.accept_whitespace = ws
	});
}

t_token	token(t_token_type type)
{
	return (
		(t_token){
		.type = type
	});
}

t_token	single_char(char chr)
{
	return (
		(t_token){
		.type = TOKEN_SINGLE_CHAR,
		.as_single_char.chr = chr
	});
}
