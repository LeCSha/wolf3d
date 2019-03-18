/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:47:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/15 18:13:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	left_panel(t_pos origin, t_env *env)
{
	t_rect		rect;

	// square
	rect = (t_rect){origin.x, origin.y, 400, 450, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// create new
	rect = (t_rect){origin.x + 10, origin.y + 10, 0, 25, C_WHITE};
	ui_make_string(rect, "Create a map", env->data);
	rect = (t_rect){origin.x + 10, origin.y + 40, 300, 25, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// upload
	rect = (t_rect){origin.x + 10, origin.y + 90, 0, 25, C_WHITE};
	ui_make_string(rect, "Upload a map", env->data);
	rect = (t_rect){origin.x + 10, origin.y + 120, 380, 320, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// display maps file
	int			y;
	int			i;

	i = 0;
	while (env->menu.maps[i])
	{
		y = 310 + 40 * i;
		if (y >= 310 && y < 700)
		{
			rect = (t_rect){origin.x + 20, y, 300, 30, 0xFFFFFFFF};
			ui_make_string(rect, env->menu.maps[i], env->data);
		}
		i++;
	}
}

static void	right_panel(t_pos origin, t_env *env)
{
	t_rect		rect;

	// square
	rect = (t_rect){origin.x + 400, origin.y, 400, 450, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// start button
	rect = (t_rect){origin.x + 410, origin.y + 400, 0, 25, C_WHITE};
	ui_make_string(rect, "Start", env->data); 
	rect = (t_rect){origin.x + 410, origin.y + 400, 150, 25, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// preview
	rect = (t_rect){origin.x + 410, origin.y + 10, 380, 350, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);

	// Cancel/Exit button
	rect = (t_rect){origin.x + 610, origin.y + 400, 0, 25, C_WHITE};
	if (env->menu.state == 1)
		ui_make_string(rect, "Exit", env->data); 
	else if (env->menu.state == 2)
		ui_make_string(rect, "Cancel", env->data); 
	rect = (t_rect){origin.x + 610, origin.y + 400, 150, 25, C_WHITE};
	ui_make_square(rect, 0, 0, env->data);
}

void		menu(t_env *env)
{
	t_rect		rect;
	t_pos		origin;

	origin.x = WIN_W / 2 - 400;
	origin.y = WIN_H / 2 - 225;

	// display background
	rect = (t_rect){0, 0, WIN_W, WIN_H, 0x00000000};
	SDL_BlitScaled(env->menu.background, 0, env->data->surface,
	&((SDL_Rect){rect.x, rect.y, rect.w, rect.h}));

	// display popup
	rect = (t_rect){origin.x + 230, origin.y - 50, 0, 35, C_WHITE};
	ui_make_string(rect, "DOOM NUKEM EDITOR", env->data);

	// display left
	left_panel(origin, env);

	// display right
	right_panel(origin, env);
}