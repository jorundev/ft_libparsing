/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:43 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/12 20:53:10 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	t_parser	parser;
	t_match		match;

	parser_create(&parser,
					token(TOKEN_IDENTIFIER),
					token(TOKEN_WHITESPACES_ONE_OR_MORE),
					separator(",", 3, 1, TOKEN_NUMBER),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_END_OF_STREAM),
					token(TOKEN_FINISH_TASK)
				);
	if (!parser.is_valid)
		printf("Parser creation failed\n");
	match = parser_match(&parser, "Ceci est du parsing");
	char *str = malloc(match.descs[0].end - match.descs[0].start + 1);
	memcpy(str, match.descs[0].start, match.descs[0].end - match.descs[0].start);
	str[match.descs[0].end - match.descs[0].start] = 0;
	if (match.descs[0].status == DESC_STATUS_OK)
		printf("Match found: '%s'\n", str);
	free(str);
	return (0);
}
