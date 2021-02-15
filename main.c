/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:43 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 19:08:41 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	t_parser		parser;
	t_match			match;
	unsigned int	i;
	char *ori = "C 255, 0, 0";

	i = 0;
	parser_create(&parser,
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_IDENTIFIER),
					token(TOKEN_WHITESPACES_ONE_OR_MORE),
					token(TOKEN_NUMBER),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					single_char(','),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_NUMBER),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					single_char(','),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_NUMBER),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_FINISH_TASK)
				);
	if (!parser.is_valid)
	{
		printf("Parser creation failed\n");
		return (0);
	}
	match = parser_match(&parser, ori);
	while (match.has_matched && match.descs[i].type != TOKEN_FINISH_TASK)
	{
		char *str = desc_as_str(&match.descs[i]);
		printf("Match: '%s'\n", str);
		free(str);
		++i;
	}
	return (0);
}
