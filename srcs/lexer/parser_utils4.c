/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 11:19:50 by fmadura           #+#    #+#             */
/*   Updated: 2019/05/05 17:36:30 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		no_op_int(int c)
{
	(void)c;
	return (0);
}

int		is_mus(int c)
{
	return (c == 'm');
}