/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_maths.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmadura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 12:39:11 by fmadura           #+#    #+#             */
/*   Updated: 2018/09/07 16:28:29 by fmadura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	ft_sqr(double a)
{
	return (a * a);
}

double	ft_delta(double a, double b)
{
	return sqrt(1 + ft_sqr(a) / ft_sqr(b));
}

double	ft_pyt(double a, double b)
{
	return sqrt(ft_sqr(a) + ft_sqr(b));
}
