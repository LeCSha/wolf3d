/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_decor_images.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 23:37:56 by abaille           #+#    #+#             */
/*   Updated: 2019/05/06 16:22:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	init_doors_images(t_env *e)
{
	int	i;

	i = 0;
	while (i < NB_DOOR_IMG)
	{
		if (!(e->world.surfaces.doors[i].sprite = ui_img("decor/door/", i, 0)))
			return (0);
		i++;
	}
	return (1);
}