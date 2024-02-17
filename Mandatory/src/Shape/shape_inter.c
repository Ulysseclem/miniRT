/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/17 14:00:12 by icaharel         ###   ########.fr       */
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

// t_inter	*plane_intersect(t_shape *s, t_ray r)
// {
// 	t_inter	*xs;
// 	t_tuple	normal;
// 	float	dot;
// 	float	distance;

// 	normal = vector(0,1,0);
// 	dot = dot_product(r.direction, normal);
// 	if (dot == 0.0f)
// 		return (NULL);
// 	distance = ((s->point.x - r.origin.x) * normal.x + 
// 	(s->point.y - r.origin.y) * normal.y + 
// 	(s->point.z - r.origin.z) * normal.z) / dot;
// 	if (distance >= 0.0f)
// 	{
// 		xs = malloc(sizeof(t_inter) * 2);
// 		xs[0] = create_inter_new(distance, *s);
// 		xs[1] = create_inter_new(distance, *s);
// 		return (xs);
// 	}
// 	else
// 		return (NULL);
// }

void add_intersection(t_inter **xs, float t)
{
	if ((*xs)[0].t < 0)
		(*xs)[0].t = t;
	else if ((*xs)[1].t < 0)
		(*xs)[1].t = t;
}

t_inter	*plane_intersect(t_shape *s, t_ray r)
{
	t_inter	*xs;

	xs = malloc(sizeof(t_inter) * 2);
    if (!xs)
		return (NULL);
	xs[0] = create_inter_new(-1, *s);
    xs[1] = create_inter_new(-1, *s);
	xs->count = 2;
	add_intersection(&xs, -r.origin.y / r.direction.y);
	add_intersection(&xs, -r.origin.y / r.direction.y);
	return (xs);
}

int check_cap(t_ray r, float t, float radius)
{
	float x;
	float z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if (x * x + z * z <= radius * radius)
		return (TRUE);
	else 
		return (FALSE);
}

int intersect_caps(t_shape *s, t_ray r, t_inter *xs)
{
    float t, t1;
	int ret;
    t_cylinder *cylinder = (t_cylinder *)s->ptr_type;

	ret = 0;
    if (equal(r.direction.y, 0))
        return (ret);
    t = (-r.origin.y) / r.direction.y;
    if (t >= 0 && check_cap(r, t, cylinder->diameter/2))
    {
        add_intersection(&xs, t);
		ret++;
    }
    t1 = (cylinder->height - r.origin.y) / r.direction.y;
    if (t1 >= 0 && check_cap(r, t1, cylinder->diameter/2))
    {
        add_intersection(&xs, t1);
		ret++;
    }
    return (ret);
}

t_inter *cylinder_intersect(t_shape *s, t_ray r)
{
    t_inter *xs;
    t_cylinder *cy = (t_cylinder *)s->ptr_type;
    float t0, t1, y0, y1;

	xs = malloc(sizeof(t_inter) * 2);
    if (!xs)
        return (NULL);
    xs[0] = create_inter_new(-1, *s);
    xs[1] = create_inter_new(-1, *s);
	
    cy->a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
    if (equal(cy->a, 0))
    {
		if (intersect_caps(s, r, xs))
			return (xs);
		else
			return (free(xs), NULL);
	}
    cy->b = 2 * (r.origin.x * r.direction.x + r.origin.z * r.direction.z);
    cy->c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - pow(cy->diameter / 2, 2);
    cy->d = cy->b * cy->b - 4 * cy->a * cy->c;
    if (cy->d >= 0)
    {
        t0 = (-cy->b - sqrt(cy->d)) / (2 * cy->a);
        y0 = r.origin.y + t0 * r.direction.y;
        t1 = (-cy->b + sqrt(cy->d)) / (2 * cy->a);
        y1 = r.origin.y + t1 * r.direction.y;
        if (t0 >= 0 && y0 >= 0 && y0 <= cy->height)
            add_intersection(&xs, t0);
        if (t1 >= 0 && y1 >= 0 && y1 <= cy->height)
            add_intersection(&xs, t1);
    }
    if (intersect_caps(s, r, xs) == 0 && cy->d < 0)
		return (free(xs), NULL);
    return (xs);
}
