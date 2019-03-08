/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <fmadura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:47:46 by fmadura           #+#    #+#             */
/*   Updated: 2019/03/06 18:48:43 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
** Check where the hole is and whether we're bumping into a wall.
*/
int		is_bumping(const t_sector *sect, float eyeheight,
		unsigned s, t_engine *e)
{
	float			hole_low;
	float			hole_high;

	if (sect->neighbors[s] < 0)
	{
		hole_low = 9e9;
		hole_high = -9e9;
	}
	else
	{
		hole_low = fmax(sect->floor, e->sectors[sect->neighbors[s]].floor);
		hole_high = fmin(sect->ceil, e->sectors[sect->neighbors[s]].ceil);
	}
	return (hole_high < e->player.where.z + HEADMARGIN
			|| hole_low > e->player.where.z - eyeheight + KNEEHEIGHT);
}

int		is_crossing(const t_vtx p, t_vtx d, const t_vtx *vert, unsigned s)
{
	return (intersect_rect(p, add_vertex(p, d), vert[s], vert[s + 1])
			&& pointside(add_vertex(p, d), vert[s], vert[s + 1]) < 0);
}

void	bumping_score(t_vtx *d, t_vtx b)
{
	float			x2;
	float			y2;

	x2 = b.x * b.x;
	y2 = b.y * b.y;
	d->x = b.x * (d->x * b.x + b.y * d->y) / (x2 + y2);
	d->y = b.y * (d->x * b.x + b.y * d->y) / (x2 + y2);
}