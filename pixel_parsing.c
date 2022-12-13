/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:07:47 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/13 14:17:41 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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
		z.i = 0 - (z.r * sin(c->i) - ((z.r * z.r * z.r) - z.i) * cos(c->i));
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

t_pixel	get_coordinates(double x, double y, t_complex *p)
{
	t_complex	z;
	t_pixel		pixel;

	z.r = p->pos.x + (x - W_WIDTH / 2) / p->z.x;
	z.i = p->pos.y + (y - W_HGT / 2) / p->z.y;
	pixel.c = z;
	if (p->name == 1)
		pixel.i = iteration_nb_mandelbrot(z, p);
	else if (p->name == 2)
		pixel.i = iteration_nb_oscil(z, p);
	else
		pixel.i = iteration_nb_julia(z, p);
	return (pixel);
}

int	draw_fractal(t_data *img, t_complex *p)
{
	double	x;
	double	y;
	t_pixel	pixel;

	x = 0;
	y = 0;
	while (x < W_WIDTH)
	{
		while (y < W_HGT)
		{
			pixel = get_coordinates(x, y, p);
			p->max = round(p->max);
			if (pixel.i == p->max)
				my_mlx_pixel_put(img, x, y, 0x000000);
			else
				my_mlx_pixel_put(img, x, y, pixel.i * p->color * 1);
			y += p->definition;
		}
		y = 0;
		x += 1;
	}
	return (0);
}
