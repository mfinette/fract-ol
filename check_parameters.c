/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:19:50 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/13 15:11:08 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static	void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	check_parameter(int argc, char **argv, t_complex *p)
{
	if (argc != 3)
		return (ft_putstr(ERROR), 0);
	if (argv[1][0] == 'j' && !argv[1][1])
		p->name = 0;
	else if (argv[1][0] == 'm' && !argv[1][1])
		p->name = 1;
	else if (argv[1][0] == 'c' && !argv[1][1])
		p->name = 2;
	else
		return (ft_putstr(ERROR), 0);
	if (argv[2][0] == 'g' && !argv[2][1])
		p->definition = 1;
	else if (argv[2][0] == 'p' && !argv[2][1])
		p->definition = 2;
	else
		return (ft_putstr(ERROR), 0);
	return (1);
}
