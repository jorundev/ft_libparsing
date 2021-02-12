/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 15:01:43 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/12 17:42:18 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

int	main(void)
{
	t_parser	parser;

	parser_create(&parser,
					token(TOKEN_IDENTIFIER),
					token(TOKEN_WHITESPACES_ONE_OR_MORE),
					separator(",", 3, 1, TOKEN_NUMBER),
					token(TOKEN_WHITESPACES_ZERO_OR_MORE),
					token(TOKEN_END_OF_STREAM),
					token(TOKEN_FINISH_CREATION)
				);
	if (!parser.is_valid)
		printf("Parser creation failed\n");
	parser_match(&parser, "8Salut");
	return (0);
}
