/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 11:52:53 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/02 20:55:26 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "doom_define.h"
# include "doom_maths.h"
# include "doom_struct_assets.h"
# include "doom_struct_obj.h"
# include "doom_struct_gameplay.h"
# include "doom_engine.h"
# include "doom_struct_env.h"

int         init_consumable(t_env *env);
int		    pick_object(t_env *env, t_wrap_sect *obj);
int		    give_shield(void *e, t_wrap_inv *object);
int		    give_health(void *e, t_wrap_inv *object);

int         init_character(t_character *new);

SDL_Surface *create_surf(char *path);

int			sdl_keyhook(t_env *env, SDL_Event event);
int		    fill_objects_sector(t_sector *sector, t_vtx v, int ref);

void		LoadData(t_engine *e, t_env *env);

void		setpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32		getpixel(SDL_Surface *surface, int x, int y);

int			print_inventory(t_env *env, t_inventory *inventory, int x, int y);
int			set_inventory(t_env *env);
#endif
