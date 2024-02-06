/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:15:55 by uclement          #+#    #+#             */
/*   Updated: 2024/02/04 17:43:24 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_tuple	reflect(t_tuple vector_in, t_tuple normal)
{
	t_tuple vector_out;

	vector_out = sub_tuple(vector_in, mul_sca_tuple(normal, dot_product(vector_in, normal) * 2));
	return (vector_out);
}

float customPow(float base, int exponent) // pow custom pour eviter des nombre trop grand
{
    float result;
	int i;

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

/* ************************************************************************** */
/*	Lightning avec specular													  */
/* ************************************************************************** */


t_color lightning(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
	t_color effective_color;
	t_color	diffuse;
	t_color	specular;
	t_color ambiant;
	float	light_dot_normal;
	float	reflect_dot_eye;
	t_tuple	lightv;
	t_tuple	reflectv;

	effective_color = mul_color(m.color, l.color); // combine surface color with light color / intensivity
	ambiant = add_color(effective_color, m.ambiant);
	lightv = norm(sub_tuple(l.position, p)); // Find the direction to the light source
	light_dot_normal = dot_product(lightv, normalv);
	if (light_dot_normal < 0 || in_shadow == true)
	{
		diffuse = set_color(0, 0, 0);
		specular = set_color(0, 0, 0);
	}
	else
	{
		diffuse = mul_sca_color(mul_sca_color(effective_color, m.diffuse), light_dot_normal); // diffuse contribution
		reflectv = reflect(neg_tuple(lightv), normalv);
		reflect_dot_eye = dot_product(reflectv, eyev);
		if (reflect_dot_eye <= 0) // light reflects away from the eye
			specular = set_color(0, 0, 0);
		else
			specular = mul_sca_color(mul_sca_color(l.color, m.specular), customPow(reflect_dot_eye, m.shininess));
	}
	return (add_color(add_color(ambiant, diffuse), specular));
}

/* ************************************************************************** */
/*	Lightning sans specualr													  */
/* ************************************************************************** */

t_color lightning_no_specular(t_material m, t_light l, t_tuple p, t_tuple normalv, bool in_shadow)
{
	t_color effective_color;
	//t_color ambiant;
	t_color	diffuse;
	float	light_dot_normal;
	t_tuple	lightv;


	effective_color = mul_color(m.color, l.color); // combine surface color with light color / brightness
	//ambiant = mul_sca_color(effective_color, m.ambiant); //ambiant contribution to the final color
	lightv = norm(sub_tuple(l.position, p)); // Find the direction to the light source
	light_dot_normal = dot_product(lightv, normalv); // Represents the cosine of the angle between the light vector and the normal vector.
	if (light_dot_normal < 0 || in_shadow == true) // if neg = light is on the other side of the surface
		diffuse = set_color(0, 0, 0);
	else
		diffuse = mul_sca_color(mul_sca_color(effective_color, m.diffuse), light_dot_normal); // diffuse contribution to the final color
	return (add_color(effective_color, diffuse));
}