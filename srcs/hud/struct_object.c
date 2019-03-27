/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:18:41 by abaille           #+#    #+#             */
/*   Updated: 2019/03/26 11:45:08 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	object_new(t_object *new, int i, int max_stack)
{
    new->max_stack = max_stack;
	if ((new->sprite = ui_img("consumable/", i)))
	    return (1);
    return (0);
}

int	init_inventory(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		env->player.inventory.objects[i] = (t_wrap_inv) {NULL, 0, 0, {{{0, 0}, {0, 0}}, {{0, 0}, {0, 0}}}};
		i++;
	}
	env->hud.inventory.is_active = 0;
	return (1);
}

int	init_consumable(t_env *env)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_OBJECTS)
	{
		if (i < WORLD_NB_CSMBLE)
		{
			if (!object_new(&env->world.objects[i], i, i == 5 ? 1 : 5))
				return (0);
		}
		else
		{
			if (!object_new(&env->world.objects[i], i, 0))
				return (0);
		}

		i++;
	}
	return (init_inventory(env));
}