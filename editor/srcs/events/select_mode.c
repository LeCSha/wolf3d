/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 16:12:22 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/17 02:05:28 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		unselect_all(t_env *env)
{
	env->obj_select = 0;
	env->vtx_select = 0;
	env->sct_select = 0;
}

static void     reset_values(t_env *env)
{
	// reset menu input new
	get_element(E_I_SELEC_HEIGHT, env)->clicked = 0;
	get_element(E_I_SELEC_HEIGHT, env)->color = C_WHITE;
}

static void     delete_object(t_object *obj, t_env *env)
{
	t_object	*ptr;

	ptr = env->objects;
	if (ptr == obj)
	{
		env->objects = ptr->next;
		lt_release(obj->name);
		lt_release(obj);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == obj)
		{
			ptr->next = ptr->next->next;
			lt_release(obj->name);
			lt_release(obj);
		}
		ptr = ptr->next;
	}
}

static void		delete_sct_content(t_sct *sector)
{
	t_vtx	*tmp;

	while (sector->vtx_start)
	{
		tmp = sector->vtx_start->next;
		lt_release(sector->vtx_start);
		sector->vtx_start = tmp;
	}
}

static void     delete_sector(t_sct *sector, t_env *env)
{
	t_sct		*ptr;

	ptr = env->sct_start;
	if (ptr == sector)
	{
		env->sct_start = ptr->next;
		delete_sct_content(sector);
		lt_release(sector);
		return ;
	}
	while (ptr && ptr->next)
	{
		if (ptr->next == sector)
		{
			ptr->next = ptr->next->next;
			delete_sct_content(sector);
			lt_release(sector);
		}
		ptr = ptr->next;
	}
}

int			select_mode(t_env *env)
{
	const t_pos		m = env->data->mouse;
	const SDL_Event event = env->data->sdl.event;
	const SDL_Rect  rect = (SDL_Rect){20, 100, 850, 680};

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		reset_values(env);
		if (ui_mouseenter(env->data->mouse.x, env->data->mouse.y, rect))
		{
			unselect_all(env);
			if (env->vtx_hover)
				env->vtx_select = env->vtx_hover;
			else if (env->obj_hover)
				env->obj_select = env->obj_hover;
			else if (env->sct_hover)
			{
				env->sct_select = env->sct_hover;
				// height input
				if (get_element(E_I_SELEC_HEIGHT, env)->str)
					lt_release(get_element(E_I_SELEC_HEIGHT, env)->str);
				if (env->sct_select->height > 0
				&& !(get_element(E_I_SELEC_HEIGHT, env)->str =
				lt_push(ft_itoa(env->sct_select->height), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory");
				// gravity input
				if (get_element(E_I_SELEC_GRAVITY, env)->str)
					lt_release(get_element(E_I_SELEC_GRAVITY, env)->str);
				if (env->sct_select->gravity > 0
				&& !(get_element(E_I_SELEC_GRAVITY, env)->str =
				lt_push(ft_itoa(env->sct_select->gravity), ft_memdel)))
					ui_error_exit_sdl("Editor: Out of memory");
			}
			return (1);
		}
		else if (env->sct_select
		&& ui_mouseenter(m.x, m.y, get_element(E_I_SELEC_HEIGHT, env)->rect))
		{
			get_element(E_I_SELEC_HEIGHT, env)->clicked = 1;
			get_element(E_I_SELEC_HEIGHT, env)->color = C_GREEN;
		}
		else if (env->sct_select
		&& ui_mouseenter(m.x, m.y, get_element(E_I_SELEC_GRAVITY, env)->rect))
		{
			get_element(E_I_SELEC_GRAVITY, env)->clicked = 1;
			get_element(E_I_SELEC_GRAVITY, env)->color = C_GREEN;
		}
		else if (ui_mouseenter(m.x, m.y, get_element(E_B_SELEC_DEL, env)->rect))
		{
			if (env->obj_select)
				delete_object(env->obj_select, env);
			else if (env->sct_select)
				delete_sector(env->sct_select, env);
			unselect_all(env);
			return (1);	
		}
	}
	else if (event.type == SDL_KEYDOWN)
	{
		char				*tmp;
		char 				*key = (char *)SDL_GetKeyName(SDL_GetKeyFromScancode(
		env->data->sdl.event.key.keysym.scancode));
		const SDL_Scancode	scancode = env->data->sdl.event.key.keysym.scancode;
		int					newsize;

		if (get_element(E_I_SELEC_HEIGHT, env)->clicked == 1)
		{
			if (scancode >= 89 && scancode <= 98)
			{ // numeric keypad
				key += 7;
			}
			if ((scancode >= 89 && scancode <= 98)
			|| (scancode >= 30 && scancode <= 39))
			{
				if (get_element(E_I_SELEC_HEIGHT, env)->str_max == 0)
				{
					tmp = get_element(E_I_SELEC_HEIGHT, env)->str;
					if (!(get_element(E_I_SELEC_HEIGHT, env)->str =
					lt_push(ft_zstrjoin(get_element(E_I_SELEC_HEIGHT, env)->str, key), ft_memdel)))
						ui_error_exit_sdl("Editor: Out of memory");
					env->sct_select->height = ft_atoi(
					get_element(E_I_SELEC_HEIGHT, env)->str);
					lt_release(tmp);
				}
			}
			else if (scancode == 42)
			{
				if (get_element(E_I_SELEC_HEIGHT, env)->str)
				{
					newsize = ft_strlen(
					get_element(E_I_SELEC_HEIGHT, env)->str) - 1;
					if (newsize > 0)
						get_element(E_I_SELEC_HEIGHT, env)->str[newsize] = 0;
					else
						lt_release(get_element(E_I_SELEC_HEIGHT, env)->str);
				}
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
				if (get_element(E_I_SELEC_GRAVITY, env)->str_max == 0)
				{
					tmp = get_element(E_I_SELEC_GRAVITY, env)->str;
					if (!(get_element(E_I_SELEC_GRAVITY, env)->str =
					lt_push(ft_zstrjoin(get_element(E_I_SELEC_GRAVITY, env)->str, key), ft_memdel)))
						ui_error_exit_sdl("Editor: Out of memory");
					env->sct_select->gravity = ft_atoi(
					get_element(E_I_SELEC_GRAVITY, env)->str);
					lt_release(tmp);
				}
			}
			else if (scancode == 42)
			{
				if (get_element(E_I_SELEC_GRAVITY, env)->str)
				{
					newsize = ft_strlen(
					get_element(E_I_SELEC_GRAVITY, env)->str) - 1;
					if (newsize > 0)
						get_element(E_I_SELEC_GRAVITY, env)->str[newsize] = 0;
					else
						lt_release(get_element(E_I_SELEC_GRAVITY, env)->str);
				}
			}
			return (1);
		}
		return (0);
	}

	if (env->data->mouse.x || env->data->mouse.y)
		return (1);
	return (0);
}
