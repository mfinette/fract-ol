/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:07:47 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/17 15:45:09 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_pixel	get_coordinates(double x, double y, t_complex *p)
{
	t_complex	z;
	t_pixel		pixel;

	z.r = p->pos.x + (x - W_WIDTH / 2) / p->z.x;
	z.i = p->pos.y + (y - W_HGT / 2) / p->z.y;
	pixel.c = z;
	if (p->name == 0)
		pixel.i = iteration_nb_mandelbrot(z, p);
	else if (p->name == 10)
		pixel.i = iteration_nb_oscil(z, p);
	else
		pixel.i = iteration_nb_julia(z, p);
	return (pixel);
}

int	draw_fractal(t_complex *p)
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
				my_mlx_pixel_put(&p->img, x, y, 0x151515);
			else
				my_mlx_pixel_put(&p->img, x, y, 0xFFFFFF);
			y += p->definition;
		}
		y = 0;
		x += 1;
	}
	return (0);
}

void	render_fractal(t_thread *t)
{
	double	x;
	double	y;
	t_pixel	pixel;
	int	color;
	double	n_color;

	x = W_WIDTH / (MAX_THREADS) * t->id;
	y = 0;
	while (x < W_WIDTH / (MAX_THREADS) * (t->id + 1))
	{
		while (y < W_HGT)
		{
			pixel = get_coordinates(x, y, t->c);
			t->c->max = round(t->c->max);
			if (pixel.i == t->c->max)
				my_mlx_pixel_put(&t->c->img, x, y, 0x151515);
			else
			{
				color = pixel.i * 256 / t->c->max;
				n_color = 0;
				n_color = t->c->color + ((color / 8) << 24 | (color) << 16 | (color / 2) << 8 | 0);
				// my_mlx_pixel_put(&t->c->img, x, y, pixel.i * t->c->color * 1);
				my_mlx_pixel_put(&t->c->img, x, y, n_color);
			}
			y += t->c->definition;
		}
		x+= t->c->definition;
		y = 0;
	}
}

void	render(t_complex *p)
{
	int			i;
	t_thread	t[MAX_THREADS];

	if (p->render)
		return ;
	mlx_clear_window(p->window.mlx, p->window.win);
	p->render = 1;
	i = -1;
	while (++i < MAX_THREADS)
	{
		t[i].id = i;
		t[i].c = p;
		pthread_create(&t[i].thread, NULL, (void *)render_fractal, &t[i]);
	}
	i = -1;
	while (++i < MAX_THREADS)
		pthread_join(t[i].thread, NULL);
	mlx_put_image_to_window(p->window.mlx, p->window.win, p->img.img, 0, 0);
	p->render = 0;
}
