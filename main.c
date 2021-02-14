/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:43 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/13 19:44:47 by hroussea         ###   ########lyon.fr   */
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

	i = 0;
	parser_create(&parser,
					token(TOKEN_WHITESPACES_ONE_OR_MORE),
					single_char(','),
					token(TOKEN_FINISH_TASK)
				);
	if (!parser.is_valid)
		printf("Parser creation failed\n");

	char *ori = "  	   salut	 les amis";
	printf("Original string: '%s'\n", ori);
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
