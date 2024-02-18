/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:15:55 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 12:50:08 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_light	light(t_tuple position, t_color color)
{
	t_light	l;

	l.position = position;
	l.color = color;
	return (l);
}

t_tuple	reflect(t_tuple vector_in, t_tuple normal)
{
	t_tuple	vector_out;

	vector_out = sub_tuple(vector_in, \
	mul_sca_tuple(normal, dot_product(vector_in, normal) * 2));
	return (vector_out);
}

float	custom_pow(float base, int exponent)
{
	float	result;
	int		i;

	result = base;
	i = 0;
	if (exponent == 0)
		return (1);
	while (i < exponent)
	{
		if (result > 1)
			return (result);
		result *= base;
		i++;
	}
	return (result);
}

t_color	lightning(t_comps c, t_light l, bool in_shadow)
{
	t_lightning	var;

	var.effective_color = mul_color(c.shape.material.color, l.color);
	var.ambiant = mul_color(var.effective_color, c.shape.material.ambiant);
	var.lightv = norm(sub_tuple(l.position, c.p));
	var.light_dot_normal = dot_product(var.lightv, c.normalv);
	if (in_shadow == true)
		return (var.ambiant);
	if (c.shape.type != PLANE && var.light_dot_normal < 0)
		return (var.ambiant);
	else
	{
		var.diffuse = mul_sca_color(mul_sca_color(var.effective_color, \
		c.shape.material.diffuse), var.light_dot_normal);
		var.reflectv = reflect(neg_tuple(var.lightv), c.normalv);
		var.reflect_dot_eye = dot_product(var.reflectv, c.eyev);
		if (var.reflect_dot_eye <= 0)
			var.specular = set_color(0, 0, 0);
		else
			var.specular = mul_sca_color(mul_sca_color(l.color, \
			c.shape.material.specular), \
			custom_pow(var.reflect_dot_eye, c.shape.material.shininess));
	}
	return (add_color(add_color(var.ambiant, var.diffuse), var.specular));
}
