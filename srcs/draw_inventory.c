#include "doom.h"

int		use_drop_icon(t_env *env, t_edge bloc, int i)
{
	float	blocx;

	blocx = bloc.v2.x - bloc.v1.x;
	env->player.inventory.objects[i].udbox[0].v1.x = bloc.v2.x - blocx / 7;
	env->player.inventory.objects[i].udbox[0].v1.y = bloc.v1.y;
	env->player.inventory.objects[i].udbox[0].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[0].v2.y = bloc.v1.y + blocx / 7;
	draw_flat_rect(env->engine.surface,
	env->player.inventory.objects[i].udbox[0], 0x0);
	env->player.inventory.objects[i].udbox[1].v1.x = bloc.v2.x - blocx / 3;
	env->player.inventory.objects[i].udbox[1].v1.y = bloc.v2.y - blocx / 7;
	env->player.inventory.objects[i].udbox[1].v2.x = bloc.v2.x;
	env->player.inventory.objects[i].udbox[1].v2.y = bloc.v2.y;
	draw_flat_rect(env->engine.surface,
	env->player.inventory.objects[i].udbox[1], 0x0);
	return (0);
}

int		fill_bloc(t_env *env, t_edge *bloc, t_vtx *n, int i)
{
	float inter;
	float sbloc;

	inter = (float)W / 128.0;
	sbloc = (float)W / 6.0 - (float)W / 32.0;
	bloc->v1 = (t_vtx){n->x, n->y};
	n->x += sbloc;
	n->y = i < 3 ? sbloc + H / 6 : 2 * sbloc + inter + H / 6;
	bloc->v2 = (t_vtx){n->x, n->y};
	draw_flat_rect(env->engine.surface, *bloc, 0x88888888);
	if (env->player.inventory.objects[i].current)
	{
		put_img_inv(env, 
		env->world.objects[env->player.inventory.objects[i].current->ref].sprite,
		*bloc, 
		(t_edge){{(bloc->v2.x - bloc->v1.x) / 8, (bloc->v2.y - bloc->v1.y) / 8},
		{(bloc->v2.x - bloc->v1.x) / 12,(bloc->v2.y - bloc->v1.y) / 12}});
		use_drop_icon(env, *bloc, i);
	}
	n->x = i == 2 ? W / 7 : n->x + inter;
	n->y = i < 2 ? H / 6 : inter + H / 6 + sbloc;
	return (1);
}

int		fill_wpn(t_env *env, t_edge *bloc, t_vtx *n, int iter)
{
	float inter;
	float sbloc;

	inter = (float)W / 128.0;
	sbloc = (float)W / 4.0 - (float)W / 32.0;
	bloc->v1 = (t_vtx){n->x, n->y};
	n->x += sbloc;
	n->y = H - H / 6.0;
	bloc->v2 = (t_vtx){n->x, n->y};
	if (env->player.inventory.weapons[iter])
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

	(void)iter;
	inter = (float)W / 128.0;
	sbloc = (float)W / 4.0 - (float)W / 64.0;
	bloc->v1 = (t_vtx){n->x, n->y};
	n->x += sbloc;
	n->y = H - H / 8;
	bloc->v2 = (t_vtx){n->x, n->y};
	draw_flat_rect(env->engine.surface, *bloc, 0x88888888);
	// put_img_inv(env, env->player.inventory.ui.mini_wpn[iter], *bloc, (t_edge){{0, 0}, {0, 0}});
	n->x += inter;
	n->y = 	H - H / 10;
	return (1);
}

int		print_inventory(t_env *env)
{
	t_vtx	n;
	int		iter;
	t_ixy	start;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	n = (t_vtx){W / 7, H / 6};
	iter = 0;
	start.x = fabs(W / 1.4 - env->player.inventory.ui.front_pic->w);
	start.y = abs(H - env->player.inventory.ui.front_pic->h);
	draw_img(env, (t_edge){{0, 0}, {W / 1.4, H}}, env->player.inventory.ui.front_pic, start);
	while (iter < 6)
		iter += fill_bloc(env, &env->player.inventory.ui.blocs[iter], &n, iter);
	iter = 0;
	n = (t_vtx){W / 32, H - H / 3};
	while (iter < 3)
		iter += fill_wpn(env, &env->player.inventory.ui.wblocs[iter], &n, iter);
	iter = 0;
	n = (t_vtx){W / 16, H - H / 4};
	while (iter < 2)
		iter += fill_icon(env, &env->player.inventory.ui.iblocs[iter], &n, iter);
	return (0);
}