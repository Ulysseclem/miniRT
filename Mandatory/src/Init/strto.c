/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strto.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:56:04 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 13:24:44 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_color	str_to_color(const char *str, int *ret)
{
	t_color		p;
	float		c;
	char		**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		c = ft_strtof(tmp[0], 1, 1.0, 0);
		p.r = c / 255;
		c = ft_strtof(tmp[1], 1, 1.0, 0);
		p.g = c / 255;
		c = ft_strtof(tmp[2], 1, 1.0, 0);
		p.b = c / 255;
		free_2(tmp);
	}
	else
		*ret = 0;
	return (p);
}

t_material	str_to_material(const char *str, t_world *w, int *ret)
{
	t_material	m;
	t_color		c;

	c = str_to_color(str, ret);
	m.ambiant = mul_color(c, w->ambiant);
	m.color = str_to_color(str, ret);
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return (m);
}

t_tuple	str_to_point(const char *str, int *ret)
{
	t_tuple	p;
	char	**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		p.x = ft_strtof(tmp[0], 1, 1.0, 0);
		p.y = ft_strtof(tmp[1], 1, 1.0, 0);
		p.z = ft_strtof(tmp[2], 1, 1.0, 0);
		p.w = 1;
		free_2(tmp);
	}
	else
		*ret = 0;
	return (p);
}

t_tuple	str_to_vector(const char *str, int *ret)
{
	t_tuple	v;
	char	**tmp;

	tmp = ft_split(str, ',');
	if (tmp)
	{
		v.x = ft_strtof(tmp[0], 1, 1.0, 0);
		v.y = ft_strtof(tmp[1], 1, 1.0, 0);
		v.z = ft_strtof(tmp[2], 1, 1.0, 0);
		v.w = 0;
		free_2(tmp);
	}
	else
		*ret = 0;
	return (v);
}

float	ft_strtof(const char *str, int sign, float decimal, int has_dec)
{
	float	result;

	result = 0.0;
	if (*str == '-')
		sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	while (ft_isdigit(*str))
	{
		result = result * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		has_dec = 1;
		while (++str && ft_isdigit(*str))
		{
			result = result * 10.0 + (*str - '0');
			decimal *= 10.0;
		}
	}
	if (has_dec)
		result /= decimal;
	return (result * sign);
}
