/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_container.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:07:40 by fmadura           #+#    #+#             */
/*   Updated: 2019/04/03 20:27:05 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// int	init_pack_img(t_surface **pack, char *name, int limit)
// {
// 	int	i;

// 	i = 0;
// 	while (i < limit)
// 	{
// 		if (!(pack[i]->sprite = ui_img(name, i)))
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// int		init_container(t_env *env)
// {
// 	t_container	*surface;

// 	surface = &env->world.surfaces;
// 	return (init_pack_img((t_surface **)&env->world.surfaces.poster, "posters/",
// 	WORLD_NB_POSTERS)
// 	&& init_pack_img((t_surface **)&env->world.surfaces.walls, "walls/",
// 	WORLD_NB_WALLS)
// 	&& init_pack_img((t_surface **)&env->world.surfaces.floors, "floors/",
// 	WORLD_NB_FLOORS)
// 	&& init_pack_img((t_surface **)&env->world.surfaces.hud, "hud/",
// 	NB_HUD_OBJ)
// 	&& init_pack_img((t_surface **)&env->world.enemies, "enemies/",
// 	WORLD_NB_ENEMIES));
// }

int		init_walls(t_container *surface)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_WALLS)
	{
		if (!(surface->walls[i].sprite = ui_img("walls/", i)))
			return (0);
		i++;
	}
	return (1);
}

int		init_posters(t_container *surface)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_POSTERS)
	{
		if (!(surface->poster[i].sprite = ui_img("posters/", i)))
			return (0);
		i++;
	}
	return (1);
}

int		init_floors(t_container *surface)
{
	int	i;

	i = 0;
	while (i < WORLD_NB_FLOORS)
	{
		if (!(surface->floors[i].sprite = ui_img("floors/", i)))
			return (0);
		i++;
	}
	return (1);
}

int		init_hud(t_container *surface)
{
	int	i;

	i = 0;
	while (i < NB_HUD_OBJ)
	{
		if (!(surface->hud[i].sprite = ui_img("hud/", i)))
			return (0);
		i++;
	}
	return (1);
}

int		load_enemies(t_world *container)
{
	int		i;
	int		j;
	// char	*tmp;
	// int		ret;

	i = 0;
	// ret = 0;
	while (i < WORLD_NB_ENEMIES)
	{
		j = 0;
			// printf("i %i\n", i);
		while (j < 6)
		{
		// tmp = NULL;
		// if ((tmp = ft_itoa(i) && tmp = (ft_strrjoin("enemies/", tmp))
			if (!(container->enemies[i].sprites[j] = ui_img("enemies/suitguy/", j)))
				return (0);
			// printf("sprite init\n");
			// printf("j %i\n", j);
		// 	ret = 1;
		// else
		// 	ret = 0;
		// if (tmp)
		// 	free(tmp);
		// if (!ret)
			j++;
		}
		i++;
	}
	return (1);
}

int		init_container(t_env *env)
{
	t_container	*surface;

	surface = &env->world.surfaces;
	return (init_walls(surface)
	&& init_floors(surface)
	&& init_posters(surface)
	&& init_hud(surface)
	&& load_enemies(&env->world));
}