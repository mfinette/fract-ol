/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:40:28 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/12 17:49:52 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_initial_parameters(t_complex *p);

int mouse_action(int keycode, int x, int y, t_complex *p)
{
	double	x_pos;
	double	y_pos;
	
	x_pos = (x - W_WIDTH / 2) / p->z.x;
	y_pos = (y - W_HGT / 2) / p->z.y;	
	if (keycode == 4)
	{
		p->pos.x += 0.173 * x_pos;
		p->pos.y += 0.173 * y_pos;
		p->z.x *= 1.2;
		p->z.y *= 1.2;
		p->max += 0.5;
	}
	if (keycode == 5)
	{
		p->max -= 0.5;
		p->z.x *= 0.8;
		p->z.y *= 0.8;
	}
	draw_fractal(&p->img, p);
	mlx_put_image_to_window(p->window.mlx, p->window.win, p->img.img, 0, 0);	
	printf("%d\n", keycode);
	printf("pos.x = %lf pos.y = %lf\n", x_pos, y_pos);
	return(0);
}

int	hook_action(int keycode, t_complex *p)
{
	if (keycode == 88) // 6 numpad
		p->pos.x += 20 / p->z.x;
	if (keycode == 86) // 4 numpad
		p->pos.x -= 20 / p->z.x;
	if (keycode == 91) // 8 numpad
		p->pos.y -= 20 / p->z.x;
	if (keycode == 87) // 5 numpad
		p->pos.y += 20 / p->z.x;
	if (keycode == 124) // arrow_right
		p->r += 0.005;
	if (keycode == 123) // arrow_left
		p->r -= 0.005;
	if (keycode == 126) // arrow_up
		p->i += 0.005;
	if (keycode == 125) // arrow_down
		p->i -= 0.005;
	if (keycode == 89) // 7 numpad
		// if (p->color >= 10000)
			p->color -= 1;
	if (keycode == 92) // 9 numpad
		p->color += 1;
	if (keycode == 69) // + numpad
	{
		p->z.x *= 1.2;
		p->z.y *= 1.2;
		p->max += 0.5;
	}
	if (keycode == 78) // - numpad
	{
		p->max -= 0.5;
		p->z.x *= 0.8;
		p->z.y *= 0.8;
	}
	if (keycode == 49) // space numpad
		set_initial_parameters(p);
	if (keycode == 18)
	{
		if (p->color == 330000)
			p->color = 330500;
		else if (p->color == 330500)
			p->color = 328200;
		else if (p->color == 328200)
			p->color = 327700;
		else
			p->color = 330000;
	}
	if (keycode == 19)
		p->color = 587000;
	if (keycode == 20)
		p->color = 330000 + 60000 + 7000;
	
	if (keycode == 21)
		p->color = 1640000;
	if (keycode == 23)
	{
		if (p->color == 1770000)
			p->color = 1639946;
		else
			p->color = 1770000;
	}
	if (keycode == 22)
		p->color = 4780000;
	if (keycode == 28)
		p->color = 4850000;
	if (keycode == 26)
		p->color = 15270000;
	draw_fractal(&p->img, p);
	mlx_put_image_to_window(p->window.mlx, p->window.win, p->img.img, 0, 0);		
	printf("key pressed = %d\n", keycode);
	printf("color = %f\n", p->color);
	return (0);
}

void	set_initial_parameters(t_complex *p)
{
	p->r = 1;
	p->i = 0;
	p->z.x = 200;
	p->z.y = 200;
	//p->color = 330000 +/* 600000 */ 70000;
	p->max = 30;
	p->pos.x = 0;
	p->pos.y = 0;
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_complex	parameter;

	parameter.r = 1;
	parameter.i = 0;
	if (argc == 2)
		parameter.r = ft_atof(argv[1]);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, W_WIDTH, W_HGT, "J'ai tout copié sur github mettez moi cheat");
	img.img = mlx_new_image(mlx, W_WIDTH, W_HGT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	parameter.img = img;
	parameter.window.mlx = mlx;
	parameter.window.win = mlx_win;
	set_initial_parameters(&parameter);
	draw_fractal(&img, &parameter);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(mlx_win, ON_KEYDOWN, 0, hook_action, &parameter);
	mlx_hook(mlx_win, ON_MOUSEDOWN, 0, mouse_action, &parameter);
	//mlx_destroy_image(mlx, img.img);
	mlx_loop(mlx);
}
