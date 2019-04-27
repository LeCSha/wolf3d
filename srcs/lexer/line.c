/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 14:37:18 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/27 14:56:34 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_parseline	*new_line(unsigned nline)
{
	t_parseline	*new;

	if ((new = (t_parseline *)malloc(sizeof(t_parseline))) == NULL)
		return (NULL);
	new->first = NULL;
	new->next = NULL;
	new->nline = nline;
	new->len = 0;
	return (new);
}