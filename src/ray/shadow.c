/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:29:09 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/31 10:57:28 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

bool	is_shadowed(t_world w, t_tuple point)
{
	float	distance;
	t_ray 	ray;	
	t_inter *xs;
	t_inter	hit_xs;

	ray.origin = point;
	distance = magnitude(sub_tuple(w.l.position, point));
	ray.direction  = norm(sub_tuple(w.l.position, point));
	xs = inter_world(w, ray);
	if (!xs)
		return false;
	hit_xs = hit(xs);
	free(xs);
	if (hit_xs.hit == true && hit_xs.t < distance)
		return true;
	else
		return false;
}