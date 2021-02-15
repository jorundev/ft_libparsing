/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroussea <hroussea@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 18:49:09 by hroussea          #+#    #+#             */
/*   Updated: 2021/02/15 19:06:19 by hroussea         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_str	desc_as_str(t_descriptor *desc)
{
	t_str			ret;
	unsigned int	i;

	i = 0;
	ret = malloc(desc->end - desc->start + 1);
	while (i < desc->end - desc->start)
	{
		ret[i] = desc->start[i];
		++i;
	}
	ret[i] = 0;
	return (ret);
}
