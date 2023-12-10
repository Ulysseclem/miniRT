/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:49:48 by uclement          #+#    #+#             */
/*   Updated: 2023/12/10 15:48:56 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ************************************************************************** */
/*					TEST SPHERE												  */
/* ************************************************************************** */

t_sphere sphere()
{
	t_sphere	s;
	static int	i = 0;

	s.point = point(0, 0, 0);
	s.radius = 1;
	s.id = i;
	i++;
	return(s);
}

float	discriminant(t_ray r, float a, float b, t_tuple s_t_r)
{
	float		c;
	(void)r;

	c = dot_product(s_t_r, s_t_r) - 1;
	return (pow(b, 2) - 4 * a * c);
}
/* ************************************************************************** */
/*					TEST SPHERE												  */
/* ************************************************************************** */

void ray(t_ray *r, t_tuple p, t_tuple v)
{
	r->origin = p;
	r->direction = v;
}

t_tuple	position(t_ray r, float time)
{
	return (add_tuple(r.origin, mul_sca_tuple(r.direction, time)));
}

void	intersect(t_sphere s, t_ray r)
{
	float	a;
	float	b;
	float	d;
	t_tuple s_t_r;

	(void)s;

	s_t_r = sub_tuple(r.origin, point(0 ,0 ,0));
	a = dot_product(r.direction, r.direction);
	b = dot_product(r.direction, s_t_r) * 2;
	
	d = discriminant(r, a, b, s_t_r);
	printf("d : %f\n", d);
	if (d < 0)
		return ;
	printf("1 : %f", ((b * -1) - sqrt(d)) / (2 * a));
	printf("2 : %f", ((b * -1) + sqrt(d)) / (2 * a));

}

