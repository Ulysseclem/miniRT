/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/08 12:16:10 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


// t_inter *sphere_intersect(t_shape *s, t_ray r)
// {
// 	t_inter *xs;
// 	t_tuple s_t_r;
// 	int	size = 0;
// 	t_sphere *cur;
	
// 	cur = (t_sphere *)s->ptrType;
// 	s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
// 	cur->a = dot_product(r.direction, r.direction);
// 	cur->b = dot_product(r.direction, s_t_r) * 2;
// 	cur->c = dot_product(s_t_r, s_t_r) - 1;
// 	cur->d = pow(cur->b, 2) - (4 * cur->a * cur->c);
// 	if (cur->d >= 0)
// 			size = 2;
// 	else
// 		return (NULL);
// 	xs = malloc(sizeof(t_inter) * size);
// 	if (!xs)
// 		return (NULL);
// 	xs[0] = create_inter_new(((cur->b * -1) - sqrt(cur->d)) / (2 * cur->a), *s);
// 	xs[1] = create_inter_new(((cur->b * -1) + sqrt(cur->d)) / (2 * cur->a), *s);
// 	return(xs);	
// }

t_inter *sphere_intersect(t_shape *s, t_ray r)
{
    t_inter *xs;
    t_tuple s_t_r;
    int size = 0;
	t_sphere *current; //current

	current = (t_sphere *)s->ptrType;
	
    s_t_r = sub_tuple(r.origin, point(0,0,0));
    current->a = dot_product(r.direction, r.direction);
    current->b = 2 * dot_product(r.direction, s_t_r);
    current->c = dot_product(s_t_r, s_t_r) - (current->diameter / 2 * current->diameter / 2);
    current->d = pow(current->b, 2) - (4 * current->a * current->c);
    if (current->d >= 0)
        size = 2;
    else
        return (NULL);
    xs = malloc(sizeof(t_inter) * size);
    if (!xs)
        return (NULL);
    xs[0] = create_inter_new(((current->b * -1) - sqrt(current->d)) / (2 * current->a), *s);
    xs[1] = create_inter_new(((current->b * -1) + sqrt(current->d)) / (2 * current->a), *s);
    xs->count = 2;
    return (xs);
}

t_inter *plane_intersect(t_shape *s, t_ray r)
{
	t_inter *xs;
	t_tuple normal;
	float	dot;
	float	distance;

	normal = s->pl_dir;
	dot = dot_product(r.direction, normal);
	if (dot == 0.0f)
		return (NULL);
	distance = ((s->point.x - r.origin.x) * normal.x +
                (s->point.y - r.origin.y) * normal.y +
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