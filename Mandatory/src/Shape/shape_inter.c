/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/16 10:27:49 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_inter	*sphere_intersect(t_shape *s, t_ray r)
{
	t_inter		*xs;
	t_tuple		s_t_r;
	t_sphere	*current;

	current = (t_sphere *)s->ptr_type;
	s_t_r = sub_tuple(r.origin, point(0, 0, 0));
	current->a = dot_product(r.direction, r.direction);
	current->b = 2 * dot_product(r.direction, s_t_r);
	current->c = dot_product(s_t_r, s_t_r) - \
	(current->diameter / 2 * current->diameter / 2);
	current->d = pow(current->b, 2) - (4 * current->a * current->c);
	if (current->d < 0)
		return (NULL);
	xs = malloc(sizeof(t_inter) * 2);
	if (!xs)
		return (NULL);
	xs[0] = create_inter_new(((current->b * -1) - \
	sqrt(current->d)) / (2 * current->a), *s);
	xs[1] = create_inter_new(((current->b * -1) + \
	sqrt(current->d)) / (2 * current->a), *s);
	xs->count = 2;
	return (xs);
}

t_inter	*plane_intersect(t_shape *s, t_ray r)
{
	t_inter	*xs;
	t_tuple	normal;
	float	dot;
	float	distance;

	normal = s->pl_dir;
	dot = dot_product(r.direction, normal);
	if (dot == 0.0f)
		return (NULL);
	distance = ((s->point.x - r.origin.x) * normal.x + \
	(s->point.y - r.origin.y) * normal.y + \
	(s->point.z - r.origin.z) * normal.z) / dot;
	if (distance >= 0.0f)
	{
		xs = malloc(sizeof(t_inter) * 2);
		xs[0] = create_inter_new(distance, *s);
		xs[1] = create_inter_new(distance, *s);
		return (xs);
	}
	else
		return (NULL);
}
int check_cap(t_ray r, float t, float radius)
{
	float x;
	float z;

	x = r.origin.x + t * r.direction.x;
		// printf("or %f | ", r.origin.x);
		// printf("t %f | ", t);
		// printf("di %f\n", r.direction.x);
		// printf("x %f\n", x);
	z = r.origin.z + t * r.direction.z;
	if (x * x + z * z <= radius * radius)
		return (TRUE);
	else 
		return (FALSE);
}

void add_intersection(t_inter **xs, float t)
{
	if ((*xs)[0].t < 0)
		(*xs)[0].t = t;
	else if ((*xs)[1].t < 0)
		(*xs)[1].t = t;
}

int intersect_caps(t_shape *s, t_ray r, t_inter *xs)
{
	float t;
	float t1;
	t_cylinder *cylinder;
	
	cylinder = (t_cylinder *)s->ptr_type;
	// if (equal(r.direction.y, 0))
	// 	return (0);

	t = (-r.origin.y) / r.direction.y;
	if (t >= 0 && check_cap(r, t, cylinder->diameter/2))
	{
		add_intersection(&xs, t);
		xs->count++;

	}
	t1 = (cylinder->height - r.origin.y) / r.direction.y;
	if (t1 >= 0 && check_cap(r, t1, cylinder->diameter/2))
	{
		add_intersection(&xs, t1);
		xs->count++;
	}
	return (1);
}

t_inter *cylinder_intersect(t_shape *s, t_ray r)
{
	t_inter *xs;
	t_cylinder *cylinder;
	float a, b, c, d, t0, t1, y0, y1;

	cylinder = (t_cylinder *)s->ptr_type;
	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (equal(a, 0))
	{
		xs = malloc(sizeof(t_inter) * 2);
		if (!xs)
			return (NULL);
		xs[0] = create_inter_new(-1, *s);
		xs[1] = create_inter_new(-1, *s);
		xs->count = 0;
		intersect_caps(s, r, xs);
		if (xs->count == 0)
			return(NULL);
		return(xs);
	}
	b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
	c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - pow(cylinder->diameter / 2, 2);
	d = b * b - 4 * a * c;
	xs = malloc(sizeof(t_inter) * 2);
	if (!xs)
		return (NULL);
	xs[0] = create_inter_new(-1, *s);
	xs[1] = create_inter_new(-1, *s);
	xs->count = 0;
	if (d >= 0)
	{
		t0 = (-b - sqrt(d)) / (2 * a);
		y0 = r.origin.y + t0 * r.direction.y;
		t1 = (-b + sqrt(d)) / (2 * a);
		y1 = r.origin.y + t1 * r.direction.y;
		if (t0 >= 0 && y0 >= 1 && y0 <= cylinder->height){
			xs->count++;
			add_intersection(&xs, t0);}
		if (t1 >= 0 && y1 >= 1 && y1 <= cylinder->height){
			xs->count++;
			add_intersection(&xs, t1);}
	}
	intersect_caps(s, r, xs);
	// printf("hit %d\n", xs->count);
	if ((d < 0))
	{
		free(xs);
		return (NULL);
	}
	return (xs);
}
