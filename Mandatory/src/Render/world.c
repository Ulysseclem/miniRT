/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:09:14 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/17 13:55:00 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

float dist( t_tuple p1, t_tuple p2)
{
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    float dz = p2.z - p1.z;
    return (sqrt(dx*dx + dy*dy + dz*dz));
}

t_tuple normale_cy(t_shape s, t_tuple local_point)
{
    t_cylinder *cylinder;
	float distance;

	cylinder = (t_cylinder *)s.ptr_type;
	distance = dist(local_point, point(0, local_point.y, 0));
	
    if (distance <= cylinder->diameter/2  && local_point.y >= cylinder->height - EPSILON)
        return (vector(0, 1, 0));
	else if (distance <= cylinder->diameter/2 && local_point.y <= 0 + EPSILON)
        return (vector(0, -1, 0));
	else 
		return (vector(local_point.x, 0, local_point.z));
}

t_tuple	normale_at(t_shape s, t_tuple world_point)
{
	t_tuple		local_point;
	t_tuple		local_normal;
	t_tuple		world_normal;
	t_matrix	*inverted;
	t_matrix	*transposed;

	inverted = inverse(s.transform);
	local_point = mul_matrix_tuple(inverted, world_point);
	if (s.type == SPHERE)
		local_normal = sub_tuple(local_point, point(0, 0, 0));
	else if (s.type == PLANE)
		local_normal = vector(0,1,0);
	else if (s.type == CYLINDER)
		local_normal = normale_cy(s, local_point);
	transposed = transp_matrix(inverted);
	world_normal = mul_matrix_tuple(transposed, local_normal);
	world_normal.w = 0;
	free_matrix(inverted);
	free_matrix(transposed);
	return (norm(world_normal));
}

t_comps	prepare_computation(t_inter xs, t_ray r)
{
	t_comps	comps;

	comps.t = xs.t;
	comps.shape = xs.shape;
	comps.p = position_f(r, comps.t);
	comps.eyev = neg_tuple(r.direction);
	comps.normalv = normale_at(comps.shape, comps.p);
	comps.over_p = add_tuple(comps.p, mul_sca_tuple(comps.normalv, 0.001));
	if (dot_product(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = neg_tuple(comps.normalv);
	}
	else
		comps.inside = false;
	return (comps);
}

t_color	shade_hit(t_world w, t_comps c)
{
	bool	shadowed;

	shadowed = is_shadowed(w, c.over_p);
	return (lightning(c, w.l, shadowed));
}

t_color	color_at(t_world w, t_ray r)
{	
	t_inter	hit_xs;
	t_inter	*xs;
	t_comps	c;

	xs = inter_world(w, r);
	if (!xs)
		return (set_color(0, 0, 0));
	hit_xs = hit(xs);
	free(xs);
	if (hit_xs.hit == false)
		return (set_color(0, 0, 0));
	c = prepare_computation(hit_xs, r);
	return (shade_hit(w, c));
}
