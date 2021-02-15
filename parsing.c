/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:44:56 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 18:50:14 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token_func	create_function_pointer(t_token tk)
{
	t_token_func	fn;

	fn.token = tk;
	if (tk.type == TOKEN_IDENTIFIER)
		fn.as_std_token = &fn_identifier;
	else if (tk.type == TOKEN_NUMBER)
		fn.as_std_token = &fn_number;
	else if (tk.type == TOKEN_WHITESPACES_ZERO_OR_MORE)
		fn.as_std_token = &fn_ws0;
	else if (tk.type == TOKEN_WHITESPACES_ONE_OR_MORE)
		fn.as_std_token = &fn_ws1;
	else if (tk.type == TOKEN_SINGLE_CHAR)
		fn.as_char_token = &fn_char;
	return (fn);
}

void	parser_create(t_parser *parser, ...)
{
	va_list	args;
	t_token	tk;

	va_start(args, parser);
	parser->is_valid = 0;
	parser->nbr_fn = 0;
	while (1)
	{
		tk = va_arg(args, t_token);
		if (tk.type == TOKEN_FINISH_TASK)
			break ;
		parser->funcs[parser->nbr_fn++] = create_function_pointer(tk);
	}
	parser->is_valid = 1;
}

void	print_spaces(t_descriptor *desc, t_str str)
{
	unsigned int	i;

	i = 0;
	while (i < desc->error_index)
		if (str[i++] != '\t')
			printf(" ");
	else
		printf("\t");
}

void	display_desc_error(t_descriptor *desc, t_str str)
{
	printf(C_RED "Error:\n" C_NRM "%s" C_WHT "\n\n", desc->err_desc);
	if (!*str)
	{
		printf(C_YEL "(empty string)\n" C_NRM);
		return ;
	}
	printf(C_NRM "%.*s" C_YEL "%.1s" C_NRM "%s\n",
			desc->error_index,
			str,
			str + desc->error_index,
			str + desc->error_index + 1);
	print_spaces(desc, str);
	printf(C_YEL "^\n");
	print_spaces(desc, str);
	printf("HERE\n" C_NRM);
}
