/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 11:44:22 by abaille           #+#    #+#             */
/*   Updated: 2019/04/01 23:33:03 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_wrap_enmy	*new_enemy(t_env *env, t_vtx v, int ref)
{
	t_character	*renemy;
	t_wrap_enmy	*new;
	int			i;

	i = -1;
	if (!(new = malloc(sizeof(t_wrap_enmy))))
		return (NULL);
	ft_bzero(new, sizeof(new));
	renemy = &env->world.enemies[ref];
	new->player.where = (t_vctr){v.x, v.y, 0};
	new->player.origin = (t_vctr){v.x, v.y, 0};
	new->player.velocity = (t_vctr){0, 0, 0};
	new->player.sprite = env->player.bullet;
	new->ref = ref;
	new->frame = 0;
	new->health = renemy->health;
	new->shield = renemy->shield;
	new->damage = renemy->damage;
	new->is_alive = 1;
	if (!(new->shot = malloc(sizeof(t_impact) * 12)))
		return (NULL);
	while (++i < 12)
		ft_bzero(&new->shot[i], sizeof(t_impact));
	new->next = NULL;
	return (new);
}

int	fill_enemies_sector(t_env *env, t_sector *sector, t_vtx v, int ref)
{
	t_wrap_enmy	*iter;

	iter = NULL;
	if (sector->head_enemy == NULL)
		return ((sector->head_enemy = new_enemy(env, v, ref)) ? 1 : 0);
	iter = sector->head_enemy;
	while (iter->next != NULL)
		iter = iter->next;
	return ((iter->next = new_enemy(env, v, ref)) ? 1 : 0);
}
