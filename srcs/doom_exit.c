/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaille <abaille@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:43:01 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/16 23:48:32 by abaille          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		chk_del(void **ap)
{
	Mix_Chunk		*chunk;

	chunk = (Mix_Chunk *)(*ap);
	if (ap && *ap)
	{
		Mix_FreeChunk(chunk);
		chunk = 0;
	}
}

void		msc_del(void **ap)
{
	Mix_Music		*music;

	music = (Mix_Music *)(*ap);
	if (ap && *ap)
	{
		Mix_FreeMusic(music);
		music = 0;
	}
}

void		wdw_del(void **ap)
{
	SDL_Window      *window;

	window = (SDL_Window *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyWindow(window);
		window = 0;
	}
}

void		rdr_del(void **ap)
{
	SDL_Renderer      *renderer;

	renderer = (SDL_Renderer *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyRenderer(renderer);
		renderer = 0;
	}
}

void		srf_del(void **ap)
{
	SDL_Surface		*surface;

	surface = (SDL_Surface *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeSurface(surface);
		surface = 0;
	}
}

void		txr_del(void **ap)
{
	SDL_Texture		*texture;

	texture = (SDL_Texture *)(*ap);
	if (ap && *ap)
	{
		SDL_DestroyTexture(texture);
		texture = 0;
	}
}

void		crs_del(void **ap)
{
	SDL_Cursor		*cursor;

	cursor = (SDL_Cursor *)(*ap);
	if (ap && *ap)
	{
		SDL_FreeCursor(cursor);
		cursor = 0;
	}
}

void		ttf_del(void **ap)
{
	TTF_Font		*font;

	font = (TTF_Font *)(*ap);
	if (ap && *ap)
	{
		TTF_CloseFont(font);
		font = 0;
	}
}

void		doom_release(void)
{
	lt_destroy();
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
}

void		doom_error_exit(char *str)
{
	ft_putendl_fd(str, 2);
	doom_release();
	exit(EXIT_FAILURE);
}

void		doom_exit(void)
{
	doom_release();
	exit(EXIT_SUCCESS);
}