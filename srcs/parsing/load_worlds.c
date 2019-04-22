/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_worlds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgalasso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/22 14:46:02 by sgalasso          #+#    #+#             */
/*   Updated: 2019/04/22 18:21:05 by sgalasso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		load_worlds(t_env *env)
{
	int		fd;
	char	*line;
	int		i;

	line = 0;
	if ((fd = open("worlds", O_RDONLY)) == -1)
		doom_error_exit("Doom_nukem: fd error in load_worlds");
	if (get_next_line(fd, &line) == -1)
		doom_error_exit("Doom_nukem: gnl error in load_worlds");
	env->games = ft_memalloc(sizeof(char *) * (ft_atoi(line) + 1));
	lt_release(line);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0] == '#')
		{
			env->games[i] = ft_strdup(line + 1);
			i++;
		}
		lt_release(line);
	}
	close(fd);
}
