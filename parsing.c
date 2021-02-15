/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:44:56 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 23:02:10 by hroussea         ###   ########lyon.fr   */
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
	else if (tk.type == TOKEN_STRING)
		fn.as_str_token = &fn_str;
	else if (tk.type == TOKEN_NOT_WS_SEQ)
		fn.as_std_token = &fn_not_ws_seq;
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
	int	z_flag;

	if (!g_stop_parsing_log)
	{
		if (!*str)
		{
			printf(C_YEL "(empty string)\n" C_NRM);
			return ;
		}
		z_flag = !*(str + desc->error_index);
		desc->error_index -= z_flag;
		printf(C_NRM "%.*s" C_YEL "%.1s" C_NRM "%s\n",
				desc->error_index,
				str,
				str + desc->error_index,
				str + desc->error_index + 1);
		desc->error_index += z_flag;
		print_spaces(desc, str);
		printf(C_YEL "^\n");
		print_spaces(desc, str);
		if (!z_flag)
			printf("HERE\n" C_NRM);
		else
			printf("EARLY END OF STRING HERE\n" C_NRM);
	}
}
