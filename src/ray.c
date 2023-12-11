/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:49:48 by uclement          #+#    #+#             */
/*   Updated: 2023/12/11 14:17:23 by ulysseclem       ###   ########.fr       */
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
/* ************************************************************************** */
/*					END TEST SPHERE											  */
/* ************************************************************************** */

void	create_inter(t_inter *i, float t, t_sphere s)
{
	i->t = t;
	i->object = s;
}

float	discriminant(t_ray r, float a, float b, t_tuple s_t_r)
{
	float		c;
	(void)r;

	c = dot_product(s_t_r, s_t_r) - 1;
	return (pow(b, 2) - 4 * a * c);
}

void ray(t_ray *r, t_tuple p, t_tuple v)
{
	r->origin = p;
	r->direction = v;
}

t_inter	*intersect(t_sphere s, t_ray r)
{
	float	a;
	float	b;
	float	d;
	t_tuple s_t_r;
	t_inter *xs;

	s_t_r = sub_tuple(r.origin, point(0 ,0 ,0));
	a = dot_product(r.direction, r.direction);
	b = dot_product(r.direction, s_t_r) * 2;
	d = discriminant(r, a, b, s_t_r);   // est-ce que cela touche l'object ?
	if (d < 0)
		return ;
	xs = malloc(sizeof(t_inter) * 2);
	if (!xs)
		return (NULL);
	create_inter(&xs[0], ((b * -1) - sqrt(d)) / (2 * a), s); // premiere inter
	create_inter(&xs[1], ((b * -1) + sqrt(d)) / (2 * a), s); // deuxieme inter
	return(xs);
}

/* ************************************************************************** */
/*					Stock les interseciton dans une liste					  */
/* ************************************************************************** */
t_inter *intersections(int count, t_inter *inter) 
{
	t_inter *xs;
	int		i;
	
	xs = malloc(sizeof(t_inter) * count);
	if (!xs)
		return (NULL);
	i = 0;
	while (i < count)
	{
		xs[i] = inter[i];
		i++;
	}	
	return (xs);
}