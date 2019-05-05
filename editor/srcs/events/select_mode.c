/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/05/05 16:21:18 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	env->editor.obj_select = 0;
	env->editor.vtx_select = 0;
	env->editor.edg_select = 0;
	env->editor.sct_select = 0;

	get_element(E_B_SELEC_NORMAL, env)->clicked = 0;
	get_element(E_B_SELEC_DOOR, env)->clicked = 0;
	get_element(E_B_SELEC_FDOOR, env)->clicked = 0;
}

static int		select_input_events(t_env *env)
{
		char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));
		const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;

		if (get_element(E_I_SELEC_HCEIL, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
			|| (scancode >= 30 && scancode <= 39))
			{
				if ((input_add(E_I_SELEC_HCEIL, key, env)))
				{
					env->editor.sct_select->ceil = ft_atoi(
					get_element(E_I_SELEC_HCEIL, env)->str);
				}
			}
			else if (scancode == 42)
			{
				input_del(E_I_SELEC_HCEIL, env);
			}
			return (1);
		}
		else if (get_element(E_I_SELEC_HFLOOR, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
			|| (scancode >= 30 && scancode <= 39))
			{
				if ((input_add(E_I_SELEC_HFLOOR, key, env)))
				{
					env->editor.sct_select->floor = ft_atoi(
					get_element(E_I_SELEC_HFLOOR, env)->str);
				}
			}
			else if (scancode == 42)
			{
				input_del(E_I_SELEC_HFLOOR, env);
			}
			return (1);
		}
		else if (get_element(E_I_SELEC_GRAVITY, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
			|| (scancode >= 30 && scancode <= 39))
			{
				if ((input_add(E_I_SELEC_GRAVITY, key, env)))
				{
					env->editor.sct_select->gravity = ft_atoi(
					get_element(E_I_SELEC_GRAVITY, env)->str);
				}
			}
			else if (scancode == 42)
			{
				input_del(E_I_SELEC_GRAVITY, env);
			}
			return (1);
		}
		return (0);
}

static void		select_sector(t_env *env)
{
	const t_pos		m = env->data->mouse;
	t_elem 			*button;

	get_element(E_I_SELEC_GRAVITY, env)->clicked = 0;
	get_element(E_I_SELEC_HCEIL, env)->clicked = 0;
	get_element(E_I_SELEC_HFLOOR, env)->clicked = 0;
	get_element(E_B_SELEC_NORMAL, env)->clicked = 0;
	get_element(E_B_SELEC_DOOR, env)->clicked = 0;
	get_element(E_B_SELEC_FDOOR	, env)->clicked = 0;

	if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_NORMAL, env)->rect))
	{
		get_element(E_B_SELEC_NORMAL, env)->clicked = 1;
		env->editor.sct_select->type = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_DOOR, env)->rect))
	{
		get_element(E_B_SELEC_DOOR, env)->clicked = 1;
		env->editor.sct_select->type = 1;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_FDOOR, env)->rect))
	{
		get_element(E_B_SELEC_FDOOR	, env)->clicked = 1;
		env->editor.sct_select->type = 2;
	}
	if (ui_mouseenter(m.x, m.y,
		get_element(E_I_SELEC_HCEIL, env)->rect))
	{
		get_element(E_I_SELEC_HCEIL, env)->clicked = 1;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_I_SELEC_HFLOOR, env)->rect))
	{
		get_element(E_I_SELEC_HFLOOR, env)->clicked = 1;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_I_SELEC_GRAVITY, env)->rect))
	{
		get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_CEIL, env)->rect))
	{
		env->editor.sct_select->roof = 1;
		get_element(E_B_SELEC_CEIL, env)->clicked = 1;
		get_element(E_B_SELEC_SKY, env)->clicked = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_SKY, env)->rect))
	{
		env->editor.sct_select->roof = 0;
		get_element(E_B_SELEC_CEIL, env)->clicked = 0;
		get_element(E_B_SELEC_SKY, env)->clicked = 1;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_CEILTX, env)->rect))
	{
		get_element(E_B_SELEC_CEILTX, env)->clicked = 1;
		get_element(E_B_SELEC_FLOORTX, env)->clicked = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_FLOORTX, env)->rect))
	{
		get_element(E_B_SELEC_FLOORTX, env)->clicked = 1;
		get_element(E_B_SELEC_CEILTX, env)->clicked = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_TX_UP, env)->rect))
	{
		if (get_element(E_B_SELEC_CEILTX, env)->clicked == 1)
			(env->editor.dropdown[DD_CEILTX].idx_element < 0)
				? env->editor.dropdown[DD_CEILTX].idx_element++ : 0;
		else if (get_element(E_B_SELEC_FLOORTX, env)->clicked == 1)
			(env->editor.dropdown[DD_FLOORTX].idx_element < 0)
				? env->editor.dropdown[DD_FLOORTX].idx_element++ : 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_TX_DOWN, env)->rect))
	{
		if (get_element(E_B_SELEC_CEILTX, env)->clicked == 1)
			(env->editor.dropdown[DD_CEILTX].idx_element
			> -env->editor.dropdown[DD_CEILTX].nb_element + 1)
				? env->editor.dropdown[DD_CEILTX].idx_element-- : 0;
		else if (get_element(E_B_SELEC_FLOORTX, env)->clicked == 1)
			(env->editor.dropdown[DD_FLOORTX].idx_element
			> -env->editor.dropdown[DD_FLOORTX].nb_element + 1)
				? env->editor.dropdown[DD_FLOORTX].idx_element-- : 0;
	}
	// click music list button
	button = env->editor.dropdown[DD_CEILTX].start;
	while (button)
	{
		if (ui_mouseenter(m.x, m.y, button->rect))
		{
			env->editor.sct_select->ceiltx = button->ref;
			env->editor.dropdown[DD_CEILTX].current->clicked = 0;
			env->editor.dropdown[DD_CEILTX].current = button;
			button->clicked = 1;
		}
		button = button->next;
	}
	// click sb_txtr list button
	button = env->editor.dropdown[DD_FLOORTX].start;
	while (button)
	{
		if (ui_mouseenter(m.x, m.y, button->rect))
		{
			env->editor.sct_select->floortx = button->ref;
			env->editor.dropdown[DD_FLOORTX].current = 0;
			env->editor.dropdown[DD_FLOORTX].current = button;
			button->clicked = 1;
		}
		button = button->next;
	}
	if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
	{
		delete_sector(env->editor.sct_select, env);
		unselect_all(env);
	}
}

static int		select_edge(t_env *env)
{
	const t_pos		m = env->data->mouse;
	t_elem			*button;

	if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_SPLIT, env)->rect))
	{
		if (env->editor.edg_select->next)
		{ // normal eddge
			create_vertex(get_edge_center(
			env->editor.edg_select->vtx->pos,
				env->editor.edg_select->next->vtx->pos), env);
		}
		else
		{ // last edge
			create_vertex(get_edge_center(
			env->editor.edg_select->vtx->pos,
				env->editor.edg_select->sector->w_vtx_start->vtx->pos),
				env);
		}
		insert_w_vertex(env->editor.edg_select, env->editor.vertex, env);
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_M_WALL_UP, env)->rect))
	{
		(env->editor.dropdown[DD_MWALLTX].idx_element < 0)
		? env->editor.dropdown[DD_MWALLTX].idx_element++ : 0;
		return (1);
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_M_WALL_DOWN, env)->rect))
	{
		(env->editor.dropdown[DD_MWALLTX].idx_element
		> -env->editor.dropdown[DD_MWALLTX].nb_element + 1)
			? env->editor.dropdown[DD_MWALLTX].idx_element-- : 0;
		return (1);
	}

	// click music list button
	button = env->editor.dropdown[DD_MWALLTX].start;
	while (button)
	{
		if (ui_mouseenter(m.x, m.y, button->rect))
		{
			env->editor.dropdown[DD_MWALLTX].current->clicked = 0;
			env->editor.dropdown[DD_MWALLTX].current = button;
			button->clicked = 1;
		}
		button = button->next;
	}
	if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
	{
		delete_edge(env->editor.edg_select, env);
		unselect_all(env);
		return (1);
	}
	return (0);
}

static int		select_vertex(t_env *env)
{
	const t_pos		m = env->data->mouse;

	if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
	{
		delete_vertex(env->editor.vtx_select, env);
		unselect_all(env);
		return (1);
	}
	return (0);
}

static int		select_object(t_env *env)
{
	const t_pos		m = env->data->mouse;

	if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
	{
		delete_object(env->editor.obj_select, env);
		unselect_all(env);
		return (1);
	}
	return (0);
}

static int		select_misc(t_env *env)
{
	const t_pos		m = env->data->mouse;
	t_elem			*button;

	if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_MUSIC, env)->rect))
	{
		get_element(E_B_SELEC_MUSIC, env)->clicked = 1;
		get_element(E_B_SELEC_SBTX, env)->clicked = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_SBTX, env)->rect))
	{
		get_element(E_B_SELEC_SBTX, env)->clicked = 1;
		get_element(E_B_SELEC_MUSIC, env)->clicked = 0;
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_MISC_UP, env)->rect))
	{
		if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
			(env->editor.dropdown[DD_BGAUDIO].idx_element < 0)
				? env->editor.dropdown[DD_BGAUDIO].idx_element++ : 0;
		else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
			(env->editor.dropdown[DD_SBTX].idx_element < 0)
				? env->editor.dropdown[DD_SBTX].idx_element++ : 0;
		return (1);
	}
	else if (ui_mouseenter(m.x, m.y,
		get_element(E_B_SELEC_MISC_DOWN, env)->rect))
	{
		if (get_element(E_B_SELEC_MUSIC, env)->clicked == 1)
			(env->editor.dropdown[DD_BGAUDIO].idx_element
			> -env->editor.dropdown[DD_BGAUDIO].nb_element + 1)
				? env->editor.dropdown[DD_BGAUDIO].idx_element-- : 0;
		else if (get_element(E_B_SELEC_SBTX, env)->clicked == 1)
			(env->editor.dropdown[DD_SBTX].idx_element
			> -env->editor.dropdown[DD_SBTX].nb_element + 1)
				? env->editor.dropdown[DD_SBTX].idx_element-- : 0;
		return (1);
	}

	if (get_element(E_B_SELEC_MUSIC, env)->clicked)
	{
		// click music list button
		button = env->editor.dropdown[DD_BGAUDIO].start;
		while (button)
		{
			if (ui_mouseenter(m.x, m.y, button->rect))
			{
				env->editor.dropdown[DD_BGAUDIO].current->clicked = 0;
				env->editor.dropdown[DD_BGAUDIO].current = button;
				button->clicked = 1;
			}
			button = button->next;
		}
	}
	else
	{
		// click sb_txtr list button
		button = env->editor.dropdown[DD_SBTX].start;
		while (button)
		{
				if (ui_mouseenter(m.x, m.y, button->rect))
			{
				env->editor.dropdown[DD_SBTX].current->clicked = 0;
				env->editor.dropdown[DD_SBTX].current = button;
				button->clicked = 1;
			}
			button = button->next;
		}
	}
	return (0);
}

int				select_mode(t_env *env)
{
	SDL_Rect		rect = get_element(E_R_RECT, env)->rect;
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;

	if (env->editor.mouse_drag)
	{
		if (event.type == SDL_MOUSEBUTTONUP)
			env->editor.mouse_drag = 0;
		else
		{
			if (env->editor.vtx_select)
			{
				env->editor.vtx_select->pos = env->mouse;
				sync_sct_minmax(env);
			}
			else if (env->editor.obj_select)
			{
				env->editor.obj_select->pos = env->mouse;
			}
		}
		return (1);
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		if (ui_mouseenter(m.x, m.y, rect))
		{
			unselect_all(env);
			if (env->editor.vtx_hover)
			{
				env->editor.mouse_drag = 1;
				env->editor.vtx_select = env->editor.vtx_hover;
			}
			else if (env->editor.edg_hover)
			{
				env->editor.edg_select = env->editor.edg_hover;
			}
			else if (env->editor.obj_hover)
			{
				env->editor.mouse_drag = 1;
				env->editor.obj_select = env->editor.obj_hover;
			}
			else if (env->editor.sct_hover)
			{
				env->editor.sct_select = env->editor.sct_hover;
				// buttons
				if (env->editor.sct_hover->type == 0)
				{
					get_element(E_B_SELEC_NORMAL, env)->clicked = 1;
				}
				else if (env->editor.sct_hover->type == 1)
				{
					get_element(E_B_SELEC_DOOR, env)->clicked = 1;
				}
				else if (env->editor.sct_hover->type == 2)
				{
					get_element(E_B_SELEC_FDOOR, env)->clicked = 1;
				}
				// hceil input
				if (get_element(E_I_SELEC_HCEIL, env)->str)
					lt_release((void **)&get_element(E_I_SELEC_HCEIL, env)->str);
				if (env->editor.sct_select->ceil > 0
				&& !(get_element(E_I_SELEC_HCEIL, env)->str =
				lt_push(ft_itoa(env->editor.sct_select->ceil), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory");
				// hfloor input
				if (get_element(E_I_SELEC_HFLOOR, env)->str)
					lt_release((void **)&get_element(E_I_SELEC_HFLOOR, env)->str);
				if (env->editor.sct_select->floor > 0
				&& !(get_element(E_I_SELEC_HFLOOR, env)->str =
				lt_push(ft_itoa(env->editor.sct_select->floor), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory");
				// gravity input
				if (get_element(E_I_SELEC_GRAVITY, env)->str)
					lt_release((void **)&get_element(E_I_SELEC_GRAVITY, env)->str);
				if (env->editor.sct_select->gravity > 0
				&& !(get_element(E_I_SELEC_GRAVITY, env)->str =
				lt_push(ft_itoa(env->editor.sct_select->gravity), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory");
			}
			return (1);
		}
		else if (env->editor.sct_select)
		{
			select_sector(env);
		}
		else if (env->editor.edg_select)
		{
			select_edge(env);
		}
		else if (env->editor.obj_select)
		{
			select_object(env);
		}
		else if (env->editor.vtx_select)
		{
			select_vertex(env);
		}
		else if (!env->editor.obj_select && !env->editor.sct_select
			&& !env->editor.vtx_select && !env->editor.edg_select)
		{
		select_misc(env);
		}
		return (1);
	}
	else if (event.type == SDL_KEYDOWN)
		return (select_input_events(env));
	return (ui_mouseenter(m.x, m.y, rect) && (m.x || m.y));
}
