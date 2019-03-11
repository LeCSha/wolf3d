/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_frames.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:32:57 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/11 15:32:58 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	loop_frames(t_env *env, int *frame)
{
	if (env->player.inventory.current)
	{
		if (env->player.actions.is_loading)
		{
			if (env->player.actions.is_shooting)
			{
				*frame = 0;
				env->player.actions.is_shooting = 0;
			}
			put_gun_load(env, *frame);
			++(*frame);
		}
		else if (env->player.actions.is_shooting)
		{
			put_gun_shoot(env, *frame);
			++(*frame);
		}
		else
		{
			put_gun(env,
			env->world.armory[env->player.inventory.current->current->ref].sprite);
			*frame = 0;
		}
	}
	return (0);
}