/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_pl_weapon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:16:32 by abaille           #+#    #+#             */
/*   Updated: 2019/04/05 17:39:59 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		check_weapon_type(t_env *env, int ref)
{
	int	i;

	i = 0;
	while (i < GAME_NB_WPN)
	{
		if (env->player.inventory.weapons[i].current != NULL)
		{
			if (ref == env->player.inventory.weapons[i].current->ref)
				return (1);
		}
		i++;
	}
	return (0);
}

int		set_current_wpn(t_env *env, t_inventory *inv, int i)
{
	env->player.actions.is_shooting = 0;
	env->player.actions.is_loading = 0;
	inv->current = &inv->weapons[i];
	inv->current->ammo_current = &inv->weapons[i].ammo[0];
	inv->current->ammo_magazine = &inv->weapons[i].ammo[1];
	inv->current->damage = &inv->weapons[i].ammo[2];
	return (1);
}

int		pick_weapon(t_env *env, t_wrap_sect *obj)
{
	int			iter;
	t_weapon	*rwpn;
	t_inventory	*inv;
	t_sector	*sector;

	iter = 0;
	sector = &env->engine.sectors[env->engine.player.sector];
	inv = &env->player.inventory;
	if (env->hud.inventory.nb_wpn < 3)
	{
		iter = check_weapon_type(env, obj->ref);
		if (!iter)
		{
			rwpn = &env->world.armory[obj->ref];
			env->hud.inventory.nb_wpn++;
			inv->weapons[obj->ref].current = obj;
			inv->weapons[obj->ref].ammo[0] = rwpn->ammo_current;
			inv->weapons[obj->ref].ammo[1] = rwpn->ammo_magazine;
			inv->weapons[obj->ref].ammo[2] = rwpn->damage;
			set_current_wpn(env, inv, obj->ref);
		}
		else
			return (16);
		obj->is_picked = 1;
		sector->nb_objects--;
		return (15);
	}
	return (drop_wpn(env, env->player.inventory.current)
	? pick_weapon(env, obj) : 17);
}

int		new_current_wpn(t_env *env, t_inventory *inv)
{
	int	i;

	i = 0;
	while (i < GAME_NB_WPN)
	{
		if (inv->weapons[i].current)
			break ;
		i++;
	}
	set_current_wpn(env, inv, i);
	return (1);
}

int		drop_wpn(t_env *env, t_wrap_wpn *wpn)
{
	t_vtx	vertex;
	t_sector	*sector;
	int			ref;
	int			cur_ref;

	if (wpn != NULL)
	{
		ref = wpn->current->ref;
		cur_ref = env->player.inventory.current->current->ref;
		sector = &env->engine.sectors[env->engine.player.sector];
		vertex.x = env->engine.player.where.x + 5;
		vertex.y = env->engine.player.where.y;
		fill_objects_sector(&env->engine.sectors[env->engine.player.sector],
		vertex, wpn->current->ref, wpn->current->is_wpn);
		*wpn = (t_wrap_wpn) {NULL, 0, 0, 0, {0, 0, 0}};
		env->hud.inventory.nb_wpn--;
		env->hud.is_txt = 18;
		sector->nb_objects++;
		return (ref == cur_ref ? new_current_wpn(env, &env->player.inventory) : 1);
	}
	return (0);
}
