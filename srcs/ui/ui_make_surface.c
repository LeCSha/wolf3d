/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_make_surface.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/10 18:09:21 by sgalasso          #+#    #+#             */
/*   Updated: 2019/03/10 18:12:21 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Surface      *ui_make_surface(int height, int width)
{
	SDL_Surface     *surface;

	if (!(surface = SDL_CreateRGBSurface(
		0, width, height, 32, 0xff000000, 0xff0000, 0xff00, 0xff)))
		return (0);
	return (surface);
}