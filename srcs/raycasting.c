#include "wolf.h"

int	wolf(t_env *env, int col)
{
	int	x;
	int	y;
	t_line	line;

	x = col - 1;
	while (x < WIDTH)
	{
		line_init(env, &line, x);
		y = -1;
		while (++y < line.sdraw)
		{
			if (env->outportal == 1)
				env->portal->data[y * WIDTH + x] = env->sky->data[line_sky(env, &line, x, y - env->is_updn)];
			else
				env->mlx.data[y * WIDTH + x] = env->sky->data[line_sky(env, &line, x, y - env->is_updn)];
		}
		y--;
		while (++y <= line.edraw && y < HEIGHT)
		{
			if (env->outportal == 1)
				env->portal->data[y * WIDTH + x] = line_wall(env, &line, y -env->is_updn);
			else
				env->mlx.data[y * WIDTH + x] = line_wall(env, &line, y -env->is_updn);
		}
		y--;
		while (++y < HEIGHT)
		{
			if (env->outportal == 1)
				env->portal->data[y * WIDTH + x] = env->floor->data[line_floor(env, &line, y - env->is_updn)];
			else
				env->mlx.data[y * WIDTH + x] = env->floor->data[line_floor(env, &line, y - env->is_updn)];
		}
		x += 8;
	}
	return (0);
}
