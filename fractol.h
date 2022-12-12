/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:44:14 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/12 17:32:52 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <math.h>
# include "colors.h"
# include <stdio.h>

# define W_WIDTH 700
# define W_HGT 700
# define MAX 30

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct		s_vars
{
	void	*mlx;
	void	*win;
}					t_vars;

typedef	struct s_zoom
{
	double	x;
	double	y;
}					t_zoom;


typedef struct		s_complex
{
	double		r;
	double		i;
	t_data		img;
	t_vars		window;
	t_zoom		z;
	double		color;
	double		max;
	t_zoom		pos;
}					t_complex;

typedef struct		s_pixel
{
	t_complex	c;
	long		i;
}					t_pixel;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};


int		draw_fractal(t_data *img, t_complex *parameter);
t_pixel	get_coordinates(double x, double y, t_complex *parameter);
long	iteration_nb_julia(t_complex z, t_complex *c);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_atoi(const char *str);
float	ft_atof(char *arr);

#endif