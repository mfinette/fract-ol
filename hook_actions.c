/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:19:11 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/13 20:30:32 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_action(int keycode, int x, int y, t_complex *p)
{
	double	x_pos;
	double	y_pos;

	x_pos = (x - W_WIDTH / 2) / p->z.x;
	y_pos = (y - W_HGT / 2) / p->z.y;
	if (keycode == 4)
	{
		p->pos.x += 0.174 * x_pos;
		p->pos.y += 0.174 * y_pos;
		p->z.x *= 1.2;
		p->z.y *= 1.2;
		p->max += 0.5;
	}
	if (keycode == 5)
	{
		p->pos.x -= 0.174 * x_pos;
		p->pos.y -= 0.174 * y_pos;
		p->max -= 0.5;
		p->z.x /= 1.2;
		p->z.y /= 1.2;
	}
	render(p);
	return (0);
}

void	select_theme(int keycode, t_complex *p)
{
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
		p->color = 1770000;
	if (keycode == 20)
		p->color = 1640000;
	if (keycode == 21)
			p->color = 1639946;
	if (keycode == 23)
		p->color = 4780000;
	if (keycode == 22)
		p->color = 4850000;
	if (keycode == 28)
		p->color = 15270000;
}

void	select_fractal(int keycode, t_complex *p)
{
	if (keycode == K_J)
	{
		p->name = 1;
		set_initial_parameters(p);
	}
	if (keycode == K_M)
	{
		p->name = 2;
		set_initial_parameters(p);
	}	
	if (keycode == K_C)
	{
		p->name = 0;
		set_initial_parameters(p);
	}	
}

void	modif_params(int keycode, t_complex *p)
{
	if (keycode == PAD_6)
		p->pos.x += 20 / p->z.x;
	if (keycode == PAD_4)
		p->pos.x -= 20 / p->z.x;
	if (keycode == PAD_8)
		p->pos.y -= 20 / p->z.x;
	if (keycode == PAD_5)
		p->pos.y += 20 / p->z.x;
	if (keycode == RIGHT_A)
		p->r += 0.05;
	if (keycode == LEFT_A)
		p->r -= 0.05;
	if (keycode == UP_A)
		p->i += 0.05;
	if (keycode == DOWN_A)
		p->i -= 0.05;
	if (keycode == PAD_7)
		p->color -= 10000;
	if (keycode == PAD_9)
		p->color += 10000;
	if (keycode == SPACE)
		set_initial_parameters(p);
	if (keycode == 35)
		p->crazy *= -1;
}

int	hook_action(int keycode, t_complex *p)
{
	if (keycode == PAD_PLUS)
		p->max += 0.5;
	if (keycode == PAD_MINUS)
		p->max -= 0.5;
	if (keycode == 53)
		ft_close(p);
	select_fractal(keycode, p);
	select_theme(keycode, p);
	modif_params(keycode, p);
	render(p);
	return (0);
}
