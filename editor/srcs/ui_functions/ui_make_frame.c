/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:59:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/14 17:58:25 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ui_make_frame(void (*fc)(t_env *env), t_env *env)
{
	if ((SDL_RenderClear(env->data->sdl.renderer)) != 0)
		 ui_error_exit_sdl("Libui: Error while clearing the renderer", env->data);
	// reset surface, recoder fonction
	SDL_FillRect(env->data->surface, 0, 0xFF000000);
	/////////////////////////
	fc(env);
	if (!(env->data->texture = SDL_CreateTextureFromSurface(
	env->data->sdl.renderer, env->data->surface)))
		ui_error_exit_sdl("Libui: Error while creating the texture", env->data);
	if ((SDL_RenderCopy(env->data->sdl.renderer, env->data->texture, 0, 0)) != 0)
		ui_error_exit_sdl("Libui: Error while RenderCopy", env->data);
	SDL_DestroyTexture(env->data->texture);
	SDL_RenderPresent(env->data->sdl.renderer);
	env->data->nb_frames++;
}