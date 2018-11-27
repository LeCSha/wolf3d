#include "wolf.h"

int         put_poster(t_env *env)
{
    SDL_Rect    rect;
    int         i;

    i = 1;
    rect.w = 0;
    rect.h = 0;

    while (i < 6)
    {
        rect.x = (564 / 2) - (env->wobj.posters[i]->w / 2);
        rect.y = (564 / 2) - (env->wobj.posters[i]->h / 1.5);
        env->wobj.wposters[i] = SDL_CreateRGBSurface(0,
						564,
						563,
						32,
						0x000000FF,
						0x0000FF00,
						0x00FF0000,
						0xFF000000);
        SDL_BlitSurface(env->walls[1], NULL, env->wobj.wposters[i], NULL);
        SDL_BlitSurface(env->wobj.posters[i], NULL, env->wobj.wposters[i], &rect);
        i++;
    }
    return (0);
}

int         wall_poster(t_env *env, t_line *line)
{
    if ((env->w_map[(int)line->map.x][(int)line->map.y] >> 12)
	&& (env->w_map[(int)line->map.x][(int)line->map.y] & 0x10))
	{
        // if ((env->w_map[(int)line->map.x][(int)line->map.y] >> 12) == 7)
        //     env->wobj.poster = 2;
        // else
    		env->wobj.poster = 1;
        return (1);
	}
    return (0);
}

int         put_bullet_pxls(t_env *env, SDL_Surface *surface, int px, int py)
{
    int y;
    int x;

    y = 0;
    while (y < surface->h)
    {
        x = 0;
        while (x < surface->w)
        {
            Uint32 color = getpixel(surface, x, y);
			if (color & 0xFF000000)
				setpixel(env->wobj.simpact, x + px, y + py, color);
            x++;
        }
        y++;
    }
    return (0);
}

int         check_impact(t_line *line, t_env *env)
{
	// SDL_Rect	rect;
	int	index;

    if ((env->w_map[(int)line->map.x][(int)line->map.y] & 0xF00) != 0
    && (env->w_map[(int)line->map.x][(int)line->map.y] & 0x10) != 0)
	{
		index = env->w_map[(int)line->map.x][(int)line->map.y] >> 8;
        if (env->wobj.hit != 0)
        {
        //     // rect.w = 0;
        //     // rect.h = 0;
        //     // rect.x = env->mouse.x;
        //     // rect.y = env->mouse.y;
        //     if (env->wobj.poster == 1)
        //     {
        //         SDL_BlitSurface(env->wobj.wposters[env->w_map[(int)line->map.x][(int)line->map.y] >> 12], NULL, env->wobj.simpact, NULL);
        //         env->wobj.poster = 0;
        //     }
        //     else
        //         SDL_BlitSurface(env->walls[env->w_map[(int)line->map.x][(int)line->map.y] & 0xF], NULL, env->wobj.simpact, NULL);

		}
        // put_bullet_pxls(env, env->gun_impact, 100, 100);
        env->wobj.hit = 0;
        return (index);
    }
	return (0);
}

static int  clear_impact(t_env *env)
{
	int i;
	int j;

	j= 0;
	i = 0;
	while (i < 24)
	{
		j = 0;
		while (j < 24)
		{
			if ((env->w_map[i][j] & 0xF00) != 0)
				env->w_map[i][j] = env->w_map[i][j] & 0xF0FF;
			j++;
		}
		i++;
	}
	return (0);
}

int         wall_impact(t_env *env)
{
	int	xx;
	int	yy;

	// clear_impact(env);
	env->wobj.pos = env->pos;
	while (env->wobj.hit == 0)
	{
		xx = env->wobj.pos.x + env->dir.x * 0.2;
		yy = env->wobj.pos.y;
		if ((env->w_map[xx][yy] & 0x10) == 0)
			env->wobj.pos.x += env->dir.x * (0.2 / 2.0);
		else
			env->wobj.hit = 1;
		xx = env->wobj.pos.x;
		yy = env->wobj.pos.y + env->dir.y * 0.2;
		if ((env->w_map[xx][yy] & 0x10) == 0)
			env->wobj.pos.y += env->dir.y * (0.2 / 2.0);
		else
			env->wobj.hit = 2;
	}
	if (env->wobj.impact == 6)
	{
		clear_impact(env);
		env->wobj.impact = 1;
	}
	// printf("hexa : %x\n", (env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] = env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] & 0xF0FF) + (env->wobj.impact << 12));
	if (env->wobj.hit == 1)
		env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] = (env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] & 0xF0FF) | (env->wobj.impact << 8);
	else
		env->w_map[(int)(env->wobj.pos.x)][(int)(env->wobj.pos.y + env->dir.y * 0.2)] = (env->w_map[(int)(env->wobj.pos.x)][(int)(env->wobj.pos.y + env->dir.y * 0.2)] & 0xF0FF) | (env->wobj.impact << 8);
	// if (env->wobj.hit == 1)
	// 	env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] = env->w_map[(int)(env->wobj.pos.x + env->dir.x * 0.2)][(int)(env->wobj.pos.y)] | (1<<010);
	// else
	// 	env->w_map[(int)(env->wobj.pos.x)][(int)(env->wobj.pos.y + env->dir.y * 0.2)] = env->w_map[(int)(env->wobj.pos.x)][(int)(env->wobj.pos.y + env->dir.y * 0.2)] | (1<<010);
	return (0);
}
