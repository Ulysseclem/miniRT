/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 14:15:55 by uclement          #+#    #+#             */
/*   Updated: 2023/12/18 15:16:16 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ************************************************************************** */
/*	gestion du vecteur NORMAL												  */
/* ************************************************************************** */


// NORMALISER CETTE DAUBE
t_tuple	normale_at(t_sphere s, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	
	world_normal = vector(0, 0, 0);
	object_point = mul_matrix_tuple(inverse(s.transform), world_point); // obtenir le point and object space
	object_normal = sub_tuple(object_point, world_normal);
	world_normal = mul_matrix_tuple(transp_matrix(inverse(s.transform)), object_normal);
	world_normal.w = 0;  // remettre le w a 0 (pour vecteur) car il risque d'avoir ete change.
	return(norm(world_normal));
}

t_tuple	reflect(t_tuple vector_in, t_tuple normal)
{
	t_tuple vector_out;

	vector_out = sub_tuple(vector_in, mul_sca_tuple(normal, dot_product(vector_in, normal) * 2));
	return (vector_out);
}

void	light(t_light *l, t_tuple position, t_color color)
{
	l->position = position;
	l->intensity = color;
}

t_material	material_default()
{
	t_material	m;

	m.color = set_color(1, 1, 1);
	m.ambiant = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return(m);
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


t_color lightning(t_material m, t_light l, t_tuple p, t_tuple eyev, t_tuple normalv)
{
	t_color effective_color;
	t_color ambiant;
	t_color	diffuse;
	t_color	specular;
	float	light_dot_normal;
	float	reflect_dot_eye;
	t_tuple	lightv;
	t_tuple	reflectv;


	effective_color = mul_color(m.color, l.intensity); // combine surface color with light color / intensivity

	lightv = norm(sub_tuple(l.position, p)); // Find the direction to the light source
	ambiant = mul_sca_color(effective_color, m.ambiant); //ambiant contribution  PROBEME ICI ?
	printf("m.ambiant %f", m.ambiant);
		printf("effective colo\n");
	print_color(ambiant);
	light_dot_normal = dot_product(lightv, normalv);
	if (light_dot_normal < 0)
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
			specular = mul_sca_color(mul_sca_color(l.intensity, m.specular), customPow(reflect_dot_eye, m.shininess));
	}
	printf("\n\nasd");
	print_color(ambiant);
	print_color(specular);
	print_color(diffuse);
	printf("\n\n");

	return (add_color(add_color(ambiant, diffuse), specular));
}


/* ************************************************************************** */
/*	Lightning sans specualr													  */
/* ************************************************************************** */

t_color lightning_no_specular(t_material m, t_light l, t_tuple p, t_tuple normalv)
{
	t_color effective_color;
	t_color ambiant;
	t_color	diffuse;
	float	light_dot_normal;
	t_tuple	lightv;


	effective_color = mul_color(m.color, l.intensity); // combine surface color with light color / brightness
	ambiant = mul_sca_color(effective_color, m.ambiant); //ambiant contribution to the final color
	lightv = norm(sub_tuple(l.position, p)); // Find the direction to the light source
	light_dot_normal = dot_product(lightv, normalv); // Represents the cosine of the angle between the light vector and the normal vector.
	if (light_dot_normal < 0) // if neg = light is on the other side of the surface
		diffuse = set_color(0, 0, 0);
	else
		diffuse = mul_sca_color(mul_sca_color(effective_color, m.diffuse), light_dot_normal); // diffuse contribution to the final color
	return (add_color(ambiant, diffuse));
}