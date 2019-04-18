/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:24 by abaille           #+#    #+#             */
/*   Updated: 2019/04/18 01:43:35 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		is_pickable_object(t_env *env, t_sector *sector)
{
	t_wrap_sect *current;

	current = NULL;
	if (sector->head_object)
		current = sector->head_object;
	while (current)
	{
		if (!current->is_picked)
		{
			if (current->is_pickable)
			{
				env->hud.is_txt = pick_object(env, current);
				return (1);
			}
		}
		current = current->next;
	}
	return (0);
}

int		get_inventory_place(t_env *env)
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (env->player.inventory.objects[i].current == NULL)
			return (i);
		i++;
	}
	return (i);
}

int		check_object_type(t_wrap_inv *pack, int ref, int limit)
{
	int	i;

	i = 0;
	while (i < limit)
	{
		if (pack[i].current != NULL)
		{
			if (ref == pack[i].current->ref)
				return (i);
		}
		i++;
	}
	return (-1);
}

int		pick_gem(t_env *env, t_wrap_sect *obj, t_sector *sector)
{
	int	i;
	int	ref;

	ref = obj->ref - WORLD_NB_CSMBLE;
	(i = check_object_type(env->player.inventory.gems, obj->ref, 4)) == -1
	? env->player.inventory.gems[ref].current = obj : 0;
	i == -1 ? env->hud.shortcut[ref + 1] = &env->player.inventory.gems[ref] : 0;
	i = i == -1 ? ref : i;
	env->player.inventory.gems[i].nb_stack++;
	obj->is_picked = 1;
	sector->nb_objects--;
	Mix_PlayChannel(-1,	env->sound.hud[HUD_PCKGEM], 0);
	return (NEW_ITEM);
}

int		pick_object(t_env *env, t_wrap_sect *obj)
{
	int			index;
	int			iter;
	t_sector	*sector;

	iter = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	if (((iter = check_object_type(env->player.inventory.objects, obj->ref, 6)) > -1)
	&& !obj->is_wpn)
	{
		if (env->player.inventory.objects[iter].nb_stack >= env->world.objects[obj->ref].max_stack)
			return (FULL_STACK);
		env->player.inventory.objects[iter].nb_stack++;
		obj->is_picked = 1;
		sector->nb_objects--;
		return (NEW_ITEM);
	}
	else if (env->player.inventory.nb_current_obj < 6
	&& obj->ref < WORLD_NB_CSMBLE && !obj->is_wpn)
	{
		index = get_inventory_place(env);
		env->player.inventory.objects[index].current = obj;
		env->player.inventory.nb_current_obj++;
		env->hud.inventory.objects[index].sprite = env->world.objects[obj->ref].sprite;
		if (obj->ref == 5)
			env->hud.shortcut[0] = &env->player.inventory.objects[index];
		else
			env->player.inventory.objects[index].nb_stack++;
		obj->is_picked = 1;
		sector->nb_objects--;
		Mix_PlayChannel(-1,	env->sound.hud[HUD_PICK], 0);
		return (NEW_ITEM);
	}
	if (obj->ref >= WORLD_NB_CSMBLE && !obj->is_wpn)
		return (pick_gem(env, obj, sector));
	!obj->is_wpn ? Mix_PlayChannel(-1,	env->sound.hud[HUD_NOPE], 0) : 0;
	return (!obj->is_wpn ? FULL_INV : pick_weapon(env, obj));
}

void		drop_object(t_env *env, t_wrap_inv *object)
{
	t_vtx		vertex;
	t_sector	*sector;

	if (object->current != NULL)
	{
		sector = &env->engine.sectors[env->engine.player.sector];
		if (!object->is_used)
		{
			vertex.x = env->engine.player.where.x + 1;
			vertex.y = env->engine.player.where.y;
			fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
			vertex, object->current->ref, object->current->is_wpn);
			sector->nb_objects++;
			Mix_PlayChannel(-1,	env->sound.hud[HUD_DROP], 0);
		}
		if (object->nb_stack > 1)
			object->nb_stack--;
		else
		{
			if (object->current->ref == 5)
				env->hud.shortcut[object->current->ref] = NULL;
			ft_bzero(object, sizeof(t_wrap_inv));
			env->player.inventory.nb_current_obj--;
		}
	}
	env->hud.is_txt = ITEM_SUP;
}
