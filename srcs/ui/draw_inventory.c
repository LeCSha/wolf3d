/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_inventory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 22:17:54 by abaille           #+#    #+#             */
/*   Updated: 2019/03/11 17:11:14 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		use_drop_icon(t_env *env, t_edge bloc, int i)
{
	float	blocx;
	// t_edge	*udbox[2];
	const	SDL_Color c[2] = {{255, 255, 255, 255}, {242, 204, 42, 255}};

	blocx = bloc.v2.x - bloc.v1.x;
	env->player.inventory.objects[i].udbox[0].v1.x = bloc.v2.x - blocx / 7;
	env->player.inventory.objects[i].udbox[0].v1.y = bloc.v1.y;
	env->player.inventory.objects[i].udbox[0].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[0].v2.y = bloc.v1.y + blocx / 7;
	ui_put_string(env, (t_font){c[0], "X", F_TEXT,
	(t_vtx){env->player.inventory.objects[i].udbox[0].v1.x + 2,
	env->player.inventory.objects[i].udbox[0].v1.y}, 20, -1, -1});
	env->player.inventory.objects[i].udbox[1].v1.x = bloc.v2.x - blocx / 3;
	env->player.inventory.objects[i].udbox[1].v1.y = bloc.v2.y - blocx / 7;
	env->player.inventory.objects[i].udbox[1].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[1].v2.y = bloc.v2.y;
	draw_flat_rect(env->sdl.surface,
	env->player.inventory.objects[i].udbox[1], 0x0);
	ui_put_string(env, (t_font){c[0], "USE", F_TEXT,
	(t_vtx){env->player.inventory.objects[i].udbox[1].v1.x + 2,
	env->player.inventory.objects[i].udbox[1].v1.y}, 20, -1, -1});
	ui_put_string(env, (t_font){c[1], " ", F_NUMB,
	(t_vtx){bloc.v1.x + 8,	bloc.v1.y + 5}, 20, -1, env->player.inventory.objects[i].nb_stack});
	return (0);
}

int		fill_bloc(t_env *env, t_edge *bloc, t_vtx *n, int i)
{
	float inter;
	float sbloc;

	inter = (float)W / 128;
	sbloc = (float)W / 6 - (float)W / 32;
	bloc->v1 = *n;
	n->x += sbloc;
	n->y = i < 3 ? sbloc + H / 6 : 2 * sbloc + inter + H / 6;
	bloc->v2 = *n;
	if (env->player.inventory.objects[i].current)
	{
		put_img_inv(env, env->player.inventory.ui.box[0], *bloc, (t_edge){{0, 0}, {0, 0}});
		put_img_inv(env,
		env->world.objects[env->player.inventory.objects[i].current->ref].sprite,
		*bloc,
		(t_edge){{(bloc->v2.x - bloc->v1.x) / 8, (bloc->v2.y - bloc->v1.y) / 8},
		{(bloc->v2.x - bloc->v1.x) / 12,(bloc->v2.y - bloc->v1.y) / 12}});
		use_drop_icon(env, *bloc, i);
	}
	else
		put_img_inv(env, env->player.inventory.ui.box[1], *bloc, (t_edge){{0, 0}, {0, 0}});
	n->x = i == 2 ? W / 28 : n->x + inter;
	n->y = i < 2 ? H / 6 : inter + H / 6 + sbloc;
	return (1);
}

int		fill_wpn(t_env *env, t_edge *bloc, t_vtx *n, int iter)
{
	float inter;
	float sbloc;

	inter = (float)W / 64;
	sbloc = (float)W / 5 - (float)W / 16;
	bloc->v1 = *n;
	n->x += sbloc;
	n->y = H - H / 4.8;
	bloc->v2 = *n;
	if (env->player.inventory.weapons[iter].current)
		put_img_inv(env, env->player.inventory.ui.mini_wpn[iter], *bloc, (t_edge){{0, 0}, {0, 0}});
	else
		put_img_inv(env, env->player.inventory.ui.empt_wpn[iter], *bloc, (t_edge){{0, 0}, {0, 0}});
	n->x += inter;
	n->y = H - H / 3;
	return (1);
}

int		fill_icon(t_env *env, t_edge *bloc, t_vtx *n, int iter)
{
	float	inter;
	float	sbloc;

	inter = (float)W / 32;
	sbloc = (float)W / 6 - (float)W / 64;
	bloc->v1 = *n;
	n->x += sbloc;
	n->y = H - H / 32;
	bloc->v2 = *n;
	bloc->v2.x = iter == 0 ? bloc->v1.x + bloc->v2.x / 4.5 : bloc->v2.x - bloc->v2.x / 4.2;
	iter == 2 ? bloc->v2.x = n->x - n->x / 5.3 : 0;
	put_img_inv(env, env->player.inventory.ui.icon[iter], *bloc, (t_edge){{0, 0}, {0, 0}});
	ui_icon_data(env, (t_vtx){bloc->v2.x, bloc->v1.y}, iter);
	n->x += inter;
	n->y = 	H - H / 11;
	return (1);
}

int		print_inventory(t_env *env)
{
	t_vtx	n;
	int		iter;
	t_ixy	start;
	t_uinv	*ui;

	ui = &env->player.inventory.ui;
	start.x = fabs(W / 2.0 - ui->front_pic->w);
	start.y = abs(H - ui->front_pic->h);
	// put_img_inv(env, env->player.inventory.ui.front_pic, (t_edge){{0, 0}, {W / 1.4, H}}, (t_edge){{0, 0}, {0, 0}});
	draw_img(env, (t_edge){{0, 0}, {W / 2, H}}, ui->front_pic, start);
	ui_txt_inv(env);
	iter = 0;
	n = (t_vtx){W / 28, H / 6};
	while (iter < 6)
		iter += fill_bloc(env, &ui->blocs[iter], &n, iter);
	iter = 0;
	n = (t_vtx){W / 32, H - H / 3};
	while (iter < 3)
		iter += fill_wpn(env, &ui->wblocs[iter], &n, iter);
	iter = 0;
	n = (t_vtx){W / 24, H - H / 11};
	while (iter < 3)
		iter += fill_icon(env, &ui->iblocs[iter], &n, iter);
	return (0);
}