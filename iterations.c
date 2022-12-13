/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:36:37 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/13 18:22:28 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

long	iteration_nb_julia(t_complex z, t_complex *c)
{
	long	i;
	double	zrtemp;

	i = 0;
	while ((z.r * z.r) + (z.i * z.i) <= 4 && i < c->max)
	{
		zrtemp = z.r;
		z.r = (z.r * z.r) - (z.i * z.i) - c->r;
		z.i = (2 * zrtemp * z.i) - c->i;
		i++;
	}
	if (i == c->max)
		return (c->max);
	if (c->crazy == 1)
		return ((int)(((double)i - log2(log2((z.r * z.r) + (z.i * z.i))) + 4.0) * 20));
	else
		return (i);
}

long	iteration_nb_oscil(t_complex z, t_complex *c)
{
	long	i;
	double	zrtemp;

	i = 0;
	while ((z.r * z.r) + (z.i * z.i) <= 3 && i < c->max)
	{
		zrtemp = z.r;
		z.r = (z.r * cos(c->r) + ((z.r * z.r) - z.i) * sin(c->r));
		z.i = (z.r * sin(c->i) - ((z.r * z.r * z.r) - z.i) * cos(c->i));
		i++;
	}
	return (i);
}

long	iteration_nb_mandelbrot(t_complex z, t_complex *c)
{
	c->r = -z.r;
	c->i = z.i;
	z.r = 0;
	z.i = 0;
	return (iteration_nb_julia(z, c));
}
