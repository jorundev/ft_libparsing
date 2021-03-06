/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:43 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/19 15:09:56 by kryckely         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	make_parser(t_parser *parser)
{
	parser_create(parser,
		token_string("test"),
		token(TOKEN_WHITESPACE),
		token(TOKEN_NOT_WS_SEQ),
		token(TOKEN_WHITESPACES_ONE_OR_MORE),
		token(TOKEN_END_OF_STREAM),
		token(TOKEN_FINISH_TASK)
	);
	if (!parser->is_valid)
	{
		printf(C_RED "Parser creation failed!\n" C_NRM);
		exit(0);
	}
}

void	make_parser_file(t_parser *parser)
{
	parser_file_create(parser,
		token_string("test"),
		token(TOKEN_WHITESPACE),
		token(TOKEN_NOT_WS_SEQ),
		token(TOKEN_WHITESPACES_ONE_OR_MORE),
		token(TOKEN_END_OF_STREAM),
		token(TOKEN_FINISH_TASK)
	);
	if (!parser->is_valid)
	{
		printf(C_RED "Parser creation failed!\n" C_NRM);
		exit(0);
	}
}

int	main(int ac, char **av)
{
	t_parser		parser;
	t_match			match;
	unsigned int	i;
	char			*str;

	i = 0;
	make_parser(&parser);
	if (ac != 2)
		return (EXIT_FAILURE);
	match = parser_match(&parser, av[1]);
	while (match.has_matched && match.descs[i].type != TOKEN_FINISH_TASK)
	{
		str = desc_as_str(&match.descs[i++]);
		printf("Match: '%s'\n", str);
		free(str);
	}
	return (0);
}
