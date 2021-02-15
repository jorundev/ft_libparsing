/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:45:23 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 21:32:33 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	token_string(t_str str)
{
	return (
		(t_token){
		.type = TOKEN_STRING,
		.as_string.str = str
	});
}

t_token	token(t_token_type type)
{
	return (
		(t_token){
		.type = type
	});
}

t_token	token_char(char chr)
{
	return (
		(t_token){
		.type = TOKEN_SINGLE_CHAR,
		.as_single_char.chr = chr
	});
}
