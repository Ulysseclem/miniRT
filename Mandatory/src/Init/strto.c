/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:56:04 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 19:13:16 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_color	str_to_color(const char *str)
{
	t_color		p;
	float		c;
	char		**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		c = ft_strtof(tmp[0]);
		p.r = c / 255;
		c = ft_strtof(tmp[1]);
		p.g = c / 255;
		c = ft_strtof(tmp[2]);
		p.b = c / 255;
		free_2(tmp);
	}
	return (p);
}

t_material	str_to_material(const char *str, t_world *w)
{
	t_material	m;
	t_color		c;

	c = str_to_color(str);
	m.ambiant = mul_color(c, w->ambiant);
	m.color = str_to_color(str);
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return (m);
}

t_tuple	str_to_point(const char *str)
{
	t_tuple	p;
	char	**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		p.x = ft_strtof(tmp[0]);
		p.y = ft_strtof(tmp[1]);
		p.z = ft_strtof(tmp[2]);
		p.w = 1;
		free_2(tmp);
	}
	return (p);
}

t_tuple	str_to_vector(const char *str)
{
	t_tuple	v;
	char	**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		v.x = ft_strtof(tmp[0]);
		v.y = ft_strtof(tmp[1]);
		v.z = ft_strtof(tmp[2]);
		v.w = 0;
		free_2(tmp);
	}
	return (v);
}

float ft_strtof(const char *str)
{
	float result = 0.0;
	int sign = 1;
	int has_decimal = 0;
	float decimal_place = 1.0;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		has_decimal = 1;
		str++;
		while (ft_isdigit(*str))
		{
			result = result * 10.0 + (*str - '0');
			decimal_place *= 10.0;
			str++;
		}
	}
	if (has_decimal)
		result /= decimal_place;
	return (result * sign);
}
