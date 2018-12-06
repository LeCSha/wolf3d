/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 17:15:55 by fmadura           #+#    #+#             */
/*   Updated: 2018/10/03 17:04:34 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*line_init(t_env *env, t_line *line, int x)
{
	line->floor = env->floor;
	line->sky = env->sky;
	line->wdist = -1;
	line->sidew = -1;
	env->cam = 2 * x / (double)WIDTH - 1;
//	line->map = *point_cpy(&line->map, &env->pos);
//	point_ray(&line->raydir, &env->dir, &env->plane, env->cam);
//	point_delta(&line->delta, &line->raydir);
	line->map.x = (int)env->pos.x;
	line->map.y = (int)env->pos.y;
	line->raydir.x = env->dir.x + env->plane.x * env->cam;
	line->raydir.y = env->dir.y + env->plane.y * env->cam;
	line->delta.x = delta(line->raydir.y, line->raydir.x);
	line->delta.y = delta(line->raydir.x, line->raydir.y);
	return (line_step(env, line));
}

t_line	*line_step(t_env *env, t_line *line)
{
	if (line->raydir.x < 0)
	{
		line->step.x = -1;
		line->side.x = (env->pos.x - line->map.x) * line->delta.x;
	}
	else
	{
		line->step.x = 1;
		line->side.x = (line->map.x + 1.0 - env->pos.x) * line->delta.x;
	}
	if (line->raydir.y < 0)
	{
		line->step.y = -1;
		line->side.y = (env->pos.y - line->map.y) * line->delta.y;
	}
	else
	{
		line->step.y = 1;
		line->side.y = (line->map.y + 1.0 - env->pos.y) * line->delta.y;
	}
	return (line_dda(env, line));
}

t_line	*line_dda(t_env *env, t_line *line)
{
	while ((env->w_map[(int)line->map.x][(int)line->map.y] & 0x10) == 0)
	{
		if (line->side.x < line->side.y)
		{
			line->side.x += line->delta.x;
			line->map.x += line->step.x;
			line->sidew = 0;
		}
		else
		{
			line->side.y += line->delta.y;
			line->map.y += line->step.y;
			line->sidew = 1;
		}
	}
	// if (wall_poster(env, line) == 1)
	// {
	// 	if (check_impact(line, env) == 1)
	// 		line->text = env->wobj.simpact;
	// 	else
	// 		line->text = env->wobj.wposters[env->w_map[(int)line->map.x][(int)line->map.y] >> 12];
	// 	// else if (env->wobj.poster == 1)
	// 	// {
	// 	// 	line->text = env->wobj.wposters[env->w_map[(int)line->map.x][(int)line->map.y] >> 12];
	// 	// 	env->wobj.poster = 0;
	// 	// }
	// 	// else if (env->wobj.poster == 2)
	// 	// {
	// 	// 	// env->wobj.simpact = env->walls[1];
	// 	// 	SDL_BlitSurface(env->walls[1], NULL, env->wobj.simpact, NULL);
	// 	// 	Uint32 temps = SDL_GetTicks() / 100;
	// 	// 	SDL_BlitSurface(env->stitch[temps % 18], NULL, env->wobj.simpact, NULL);
	// 	// 	env->wobj.poster = 0;
	// 	// 	line->text = env->wobj.simpact;
	// 	// }
	// }
	if (wall_poster(env, line) == 1)
	{
		line->text = env->wobj.wposters[env->w_map[(int)line->map.x][(int)line->map.y] >> 12];
		// printf("hexa : %x\n", (env->w_map[(int)line->map.x][(int)line->map.y] & 0xF0FF) | (2 << 8));
		// printf("hexa normal : %x\n", env->w_map[(int)line->map.x][(int)line->map.y]);
	}
	else
		line->text = env->walls[env->w_map[(int)line->map.x][(int)line->map.y] & 0xF];
	if (check_impact(line, env) != 0)
	{
		printf("map : %x\n", env->w_map[(int)line->map.x][(int)line->map.y]);
		printf("wobj impact : %i\n",env->wobj.impact);
		env->wobj.is_bullet = 1;
		// SDL_BlitSurface(line->text, NULL, env->bul_surf[env->wobj.impact], NULL);
		// int y;
		// int x;

		// y = 0;
		// while (y < surface->h)
		// {
		// 	x = 0;
		// 	while (x < surface->w)
		// 	{
		// 		Uint32 color = getpixel(surface, x, y);
		// 		if (color & 0xFF000000)
		// 			setpixel(env->wobj.simpact, x + px, y + py, color);
		// 		x++;
		// 	}
		// 	y++;
		// }
	}
	// if ((env->w_map[(int)line->map.x][(int)line->map.y] & 0x100) != 0
    // && (env->w_map[(int)line->map.x][(int)line->map.y] & 0x10) != 0)
	// {
	// 	SDL_BlitSurface(line->text, NULL, env->bul_surf[env->wobj.impact], NULL);
	// }
	// else if (check_impact(line, env) == 1)
	// 	line->text = env->wobj.simpact;
	// else
	// 	line->text = env->walls[env->w_map[(int)line->map.x][(int)line->map.y] & 0xF];
	line->wdist = ldist(env, line, line->sidew == 0 ? 'x' : 'y');
	return (line_max(env, line));
}

t_line	*line_max(t_env *env, t_line *line)
{
	line->lineh = (int)(HEIGHT / line->wdist);
	line->sdraw = (-line->lineh / 2 + HEIGHT / env->hratio) + env->is_updn;
	line->sdraw < 0 ? line->sdraw = 0 : 0;
	line->edraw = (line->lineh / 2 + HEIGHT / env->hratio) + env->is_updn;
	line->edraw >= HEIGHT ? line->edraw = HEIGHT - 1 : 0;
	if (line->sidew == 0)
		line->wall.x = env->pos.y + line->wdist * line->raydir.y;
	else
		line->wall.x = env->pos.x + line->wdist * line->raydir.x;
	line->wall.x -= floor((line->wall.x));
	return (line);
}