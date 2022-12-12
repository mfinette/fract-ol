/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfinette <mfinette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:18:54 by mfinette          #+#    #+#             */
/*   Updated: 2022/12/12 14:35:22 by mfinette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

int ft_atoi(const char *str)
{
	int i;
	long long int result;
	int sign;

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

float ft_atof(char *arr)
{
	int i, j, flag;
	float val;
	char c;
	i = 0;
	j = 0;
	val = 0;
	flag = 0;
	while ((c = *(arr + i)) != '\0')
	{
		if (c != '.')
		{
			val = (val * 10) + (c - '0');
			if (flag == 1)
				--j;
		}
		if (c == '.')
		{
			if (flag == 1)
				return 0;
			flag = 1;
		}
		++i;
	}
	val = val * pow(10, j);
	return val;
}
