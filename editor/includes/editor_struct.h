/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:25:14 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/06 23:53:47 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

enum					e_type
{
	INPUT,
	BUTTON,
	RECT
};

enum					e_pages
{
	MENU,
	EDITOR,
	S_VTX,
	S_OBJ,
	S_EDG,
	S_SCT,
	S_MSC,
	DRAW,
	ELEM
};

enum					e_elements
{
	M_I_NEW,
	M_B_START,
	E_R_RECT,
	E_B_SAVE,
	E_B_MODE_SELECT,
	E_B_MODE_MOVE,
	E_B_MODE_DRAW,
	E_B_MODE_ELEM,
	E_B_ELM_UP,
	E_B_ELM_DOWN,
	E_B_DRW_UP,
	E_B_DRW_DOWN,
	E_B_ELM_OBWL,
	E_B_ELM_CONS,
	E_B_ELM_NTTY,
	E_B_ELM_PRFB,
	E_B_ELM_SPEC,
	E_B_SELEC_VTX_DEL,
	E_B_SELEC_OBJ_DEL,
	E_B_SELEC_EDG_DEL,
	E_B_SELEC_SCT_DEL,
	E_I_SELEC_HCEIL,
	E_I_SELEC_HFLOOR,
	E_I_SELEC_GRAVITY,
	E_B_SELEC_SPLIT,
	E_B_SELEC_NORMAL,
	E_B_SELEC_DOOR,
	E_B_SELEC_FDOOR,
	E_B_SELEC_CEIL,
	E_B_SELEC_SKY,
	E_B_SELEC_MUSIC,
	E_B_SELEC_SBTX,
	E_B_SELEC_MISC_UP,
	E_B_SELEC_MISC_DOWN,
	ENUM_END
};

typedef struct	s_w_vtx		t_w_vtx;
typedef struct  s_vtx   	t_vtx;
typedef struct  s_sct   	t_sct;
typedef struct	s_elem		t_elem;
typedef struct	s_object	t_object;
typedef struct	s_dropdown	t_dropdown;
typedef struct	s_menu		t_menu;
typedef struct	s_editor	t_editor;
typedef struct  s_env   	t_env;

struct					s_w_vtx
{
	int			ref;	// texture ref
	int			size;	// size edge

	t_vtx		*vtx;
	t_sct		*sector;
	t_w_vtx		*next;
};

struct					s_vtx
{
	// identifiant du w_vtx, est mis a l export
	int				id;

	t_pos			pos;
	t_vtx			*next;
};

struct					s_sct
{
	// identifiant du secteur, est mis a jour a la creation et a l export
	int				id;

	int				nb_w_vtx;
	t_w_vtx			*w_vtx_current;	// vertex wrapper
	t_w_vtx			*w_vtx_start;	// vertex wrapper

	int				close;		// is sector close;

	int				ceil;		// hauteur ceil
	int				floor;		// hauteur floor
	int				gravity;

	int				roof;		// ceil / skybox
	int				type;		// 0 normal / 1 door / 2 fdoor

	float			xmin;
	float			xmax;
	float			ymin;
	float			ymax;

	Uint32			color;		// ?

	t_sct			*next;
};

struct					s_elem
{
	int				ref;
	int				id;
	int				type;
	int				dd;			// dropdown (if part of dropdown)
	SDL_Rect		rect;
	Uint32			color;
	SDL_Surface		*image;
	Mix_Music		*audio;		// if button audio
	char			*str;		// if type == input
	int				str_max;	// if type == inpu
	
	void			(*event_fc)(t_env *);	// event ptr

	int				page;		// page (e_pages)

	int				clicked;
	int				hovered; // delete if not used ?

	t_elem			*next;
};

struct					s_object
{
	t_pos			pos;
	float			dir;	// if entity

	t_sct			*sct;
	int				ref;
	int				iswpn;	// is a weapon
	int				dd;		// dropdown
	char			*name;

	Uint32			icon_color; // replace by image
	t_object		*next;
};

enum					e_dropdowm_name
{
	DD_WALLTX,
	DD_SBTX,
	DD_BGAUDIO,
	DD_WOBJ,
	DD_CONS,
	DD_NTTY,
	DD_PRFB,
	DD_SPEC
};

struct					s_dropdown
{
	int				nb_element;
	int				idx_element;
	t_elem			*start;
	t_elem			*current;
};

struct					s_menu
{
	int				state;
	SDL_Surface		*background;
};

struct					s_editor
{
	// lst vertex
	t_vtx			*vertex;
	// lst sectors
	t_sct			*sct_current;
	t_sct			*sct_start;
	// lst objects
	t_object		*objects;

	// Error message
	time_t			timestamp;
	char			*error_msg;

	// editor dropdown lists
	t_dropdown		dropdown[12];

	// select / move / draw / element
	int				(*mode)(t_env *);

	// drag vertex;
	int				mouse_drag;
	t_pos			new_pos;

	// selected element category
	t_elem			*curr_elem_btn;
	int				curr_elem_dd;

	// grid move
	int				grid_drag;
	t_pos			grid_init_pos;
	t_pos			grid_mouse_var;
	t_pos			grid_translate;

	// hover / select
	t_vtx			*vtx_hover;
	t_w_vtx			*edg_hover;
	t_sct			*sct_hover;
	t_object		*obj_hover;

	t_vtx			*vtx_select;
	t_w_vtx			*edg_select;
	t_sct			*sct_select;
	t_object		*obj_select;

	int				oneend;		// une seule fin

	int				onespawn;	// un spawn a deja ete pose
	int				spawn_set;	// spawn pose, en attente de direction
	t_pos			spawn_pos;	// absolute pos	// pour calcul angle
	float			spawn_dir;	// direction spawn

	int				drawing;		// am i drawing an edge

	// variables
	float			grid_scale;
};

struct					s_env
{
	t_data          *data;
	char			*map_name;
	t_menu			menu;
	t_editor		editor;
	t_elem			*elements;
	t_pos			mouse;

	// data infos TO REMOVE
	int				nb_vtx;
	int				nb_sct;
};

#endif
