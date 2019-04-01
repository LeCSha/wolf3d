/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_s_engine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 13:41:58 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/01 16:10:16 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_S_ENGINE_H
# define DOOM_S_ENGINE_H

typedef struct	s_scaler	t_scaler;
typedef struct	s_sector	t_sector;
typedef struct	s_item		t_item;
typedef struct	s_engine	t_engine;
typedef struct	s_queue		t_queue;
typedef struct	s_raycast	t_raycast;
typedef struct	s_chain		t_chain;
typedef struct	s_skybox	t_skybox;


struct						s_scaler
{
	int		result;
	int		bop;
	int		fd;
	int		ca;
	int		cache;
};

struct						s_chain
{
	unsigned	a;
	unsigned	b;
	unsigned	c;
	unsigned	d;
	unsigned	e;
	unsigned	f;
	unsigned	g;
	unsigned	h;
};

struct						s_item
{
	int			sectorno;
	int			sx1;
	int			sx2;
};

struct						s_sector
{
	float		floor;
	float		ceil;
	t_vtx		*vertex;
	signed char	*neighbors;
	unsigned	npoints;
	int			nb_objects;
	t_wrap_sect	*head_object;
	t_wrap_enmy	*head_enemy;
};

struct						s_queue
{
	t_item		queue[MAXQUEUE];
	t_item		*head;
	t_item		*tail;
	t_item		now;
	t_sector	*sect;
	int			ytop[W];
	int			ybottom[W];
	int			*renderedsectors;
};

struct						s_raycast
{
	t_edge			trsl;
	t_edge			rot;
	t_edge			scale;
	t_l_float		lf_current;
	t_l_float		lf_next;
	t_l_int			li_sector;
	t_l_int			li_texture;
	t_projec		p;
	t_projec		n;
	int				x;
	int				x1;
	int				x2;
	int				txtx;
	int				neighbor;
};

struct						s_skybox
{
	SDL_Surface		*top;
	SDL_Surface		*bot;
	SDL_Surface		*left;
	SDL_Surface		*right;
	SDL_Surface		*front;
	SDL_Surface		*back;
	t_sector		sector;
};

struct						s_engine
{
	t_sector		*sectors;
	unsigned		nsectors;
	t_player		player;
	t_queue			queue;
	t_minimap		minimap;
	t_skybox		skybox;
};
#endif
