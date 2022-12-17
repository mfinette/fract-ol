/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:19:50 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/17 13:16:09 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	int	ft_atoi(const char *str)
{
	int				i;
	long long int	result;
	int				sign;

	i = 0;
	result = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result != ((result * 10 + (sign * (str[i] - '0'))) / 10))
			return ((int)((sign + 1) / 2 / -1));
		result = result * 10;
		result = result + (str[i] - 48) * sign;
		i++;
	}
	return ((int)result);
}

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

static	int	check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_strlen(str) > 3)
		return (0);
	if (ft_atoi(str) > 200)
		return (0);
	return (1);
}

int	check_parameter(int argc, char **argv, t_complex *p)
{
	if (argc != 5)
		return (ft_putstr(ERROR), 0);
	if (argv[1][0] == 'j' && !argv[1][1])
		p->name = 1;
	else if (argv[1][0] == 'm' && !argv[1][1])
		p->name = 0;
	else if (argv[1][0] == 'c' && !argv[1][1])
		p->name = 10;
	else
		return (ft_putstr(ERROR), 0);
	if (argv[2][0] == 'g' && !argv[2][1])
		p->definition = 1;
	else if (argv[2][0] == 'p' && !argv[2][1])
		p->definition = 2;
	else
		return (ft_putstr(ERROR), 0);
	if (check_str(argv[3]) && check_str(argv[4]))
	{
		p->r = (double)ft_atoi(argv[3]) / 100;
		p->i = (double)ft_atoi(argv[4]) / 100;
	}
	else
		return (ft_putstr(ERROR), 0);
	return (1);
}
