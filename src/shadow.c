/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 17:29:09 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/04 18:15:38 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_inter hit2(t_inter *xs)
{
	int 	i;
	t_inter	hit_xs;

	i = 0;
	if (!xs)
	{
		hit_xs.hit = false;
		return(hit_xs);
	}
	while(i < xs->count)
	{
		if (xs[i].t > 0)
		{
			hit_xs.t = xs[i].t;
			break;
		}
		i++;
	}
	if (xs[i].t < 0)
	{
		hit_xs.hit = false;
		return (hit_xs);
	}
	i = 0;
	while(i < xs->count)
	{
		if ((hit_xs.t > xs[i].t && xs[i].t >=0))
			hit_xs = xs[i];
		i++;
	}
	if (hit_xs.t < 0)
	{
		hit_xs.hit = false;
		return(hit_xs);
	}
	else
	{
		hit_xs.hit = true;
		return(hit_xs);
	}
}

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
	hit_xs = hit2(xs);
	free(xs);
	if (hit_xs.hit == true && hit_xs.t < distance)
	{
		return true;
	}
	else
		return false;
}