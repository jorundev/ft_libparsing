/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:47:26 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/12 17:40:55 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCS_H
# define FUNCS_H

# define	C_NRM	"\x1B[0m"
# define	C_RED	"\x1B[31m"
# define	C_GRN	"\x1B[32m"
# define	C_YEL	"\x1B[33m"
# define	C_BLU	"\x1B[34m"
# define	C_MAG	"\x1B[35m"
# define	C_CYN	"\x1B[36m"
# define	C_WHT	"\x1B[37m"

typedef char*			t_str;

typedef enum e_descstat {
	DESC_STATUS_LAST,
	DESC_STATUS_OK,
	DESC_STATUS_NOT_FOUND
}	t_desc_status;

typedef struct s_descriptor {
	char			*start;
	char			*end;
	t_str			description;
	t_desc_status	status;
	unsigned int	error_index;
}	t_descriptor;

t_descriptor	fn_identifier(t_str str)
{
	t_descriptor	ret;

	ret.start = 0;
	ret.end = 0;
	if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z')
		|| *str == '_')
	{
		ret.start = str;
		str++;
	}
	else
		return (t_descriptor){
			.status = DESC_STATUS_NOT_FOUND,
			.description = "'IDENTIFIER': expected "
							"alphabetical character or underscore",
			.error_index = 0
		};
	return (ret);
}

#endif
