/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:57:23 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 14:26:23 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	valid_range(char *str, int nbr, float min, float max)
{
	float		value[3];
	char		**param;
	int			i;

	i = 0;
	if (nbr > 1)
	{
		param = ft_split(str, ',');
		if (!param)
			return (0);
		while (i < 3)
		{
			value[i] = ft_strtof(param[i], 1, 1.0, 0);
			if (value[i] > max || value[i] < min)
				return (free_2(param), 0);
			i++;
		}
		if (equal(value[0], 0) && equal(value[1], 0) && equal(value[2], 0))
			return (free_2(param), 0);
		return (free_2(param), 1);
	}
	value[0] = ft_strtof(str, 1, 1.0, 0);
	if (value[0] > max || value[0] < min)
		return (0);
	return (1);
}

int	valid_positive_float(char *str)
{
	int	sign;

	sign = 0;
	if (*str == '-')
		return (0);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (sign == 0 && *str == '.')
			sign = 1;
		else if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	valid_float(char *str)
{
	int	sign;

	sign = 0;
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (sign == 0 && *str == '.')
			sign = 1;
		else if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	valid_tuple(char *str, float min, float max)
{
	char	**param;
	int		i;

	i = 0;
	param = ft_split(str, ',');
	if (!param)
		return (0);
	if (len_2(param) != 3)
		return (free_2(param), 0);
	while (param[i] && i++)
		if (!valid_float(param[i]))
			return (free_2(param), 0);
	if (max)
	{
		if (!valid_range(str, 3, min, max))
			return (free_2(param), 0);
	}
	free_2(param);
	return (1);
}

int	valid_rgb(char *str)
{
	int			value;
	int			i;
	char		**color;

	color = ft_split(str, ',');
	if (!color)
		return (0);
	if (len_2(color) != 3)
		return (free_2(color), 0);
	i = 0;
	while (color[i])
	{
		if (color[i][0] == '\n')
			return (free_2(color), 0);
		if (ft_strlen(color[i]) > 4)
			return (0);
		value = atoi(color[i]);
		if (value > 255 || value < 0)
			return (free_2(color), 0);
		i++;
	}
	free_2(color);
	return (1);
}
