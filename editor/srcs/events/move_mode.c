/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:14:55 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/20 22:21:40 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			move_mode(t_env *env)
{
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;

	if (ui_mouseenter(m.x, m.y, get_element(E_R_RECT, env)->rect))
	{
		if (event.type == SDL_MOUSEBUTTONDOWN && env->editor.grid_drag == 0)
		{
			env->editor.grid_init_pos = m;
			env->editor.grid_drag = 1;
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			env->editor.grid_translate.x += env->editor.grid_mouse_var.x;
			env->editor.grid_translate.y += env->editor.grid_mouse_var.y;
			ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
			ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
			env->editor.grid_drag = 0;
		}
		if (env->editor.grid_drag == 1)
		{
			env->editor.grid_mouse_var.x =
				(m.x - env->editor.grid_init_pos.x) / env->grid_scale;
			env->editor.grid_mouse_var.y =
				(m.y - env->editor.grid_init_pos.y) / env->grid_scale;
			return (1);
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		ft_bzero(&env->editor.grid_init_pos, sizeof(t_pos));
		ft_bzero(&env->editor.grid_mouse_var, sizeof(t_pos));
		env->editor.grid_drag = 0;
	}
	if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
