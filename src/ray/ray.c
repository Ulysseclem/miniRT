/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:49:48 by uclement          #+#    #+#             */
/*   Updated: 2024/01/14 13:09:15 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"



void ray(t_ray *r, t_tuple p, t_tuple v)
{
	r->origin = p;
	r->direction = v;
}

t_tuple position_f(t_ray r, float t)
{
	return (add_tuple(r.origin, mul_sca_tuple(r.direction, t)));
}

t_inter hit(t_inter *xs)
{
	int 	i;
	t_inter	hit_xs;

	i = 0;
	if (!xs)
	{
		hit_xs.hit = false;
		return(hit_xs);
	}
	hit_xs = xs[i];
	while(i < xs[0].count) // to change back to xs->count !!!
	{
		if (hit_xs.t > xs[i].t && xs[i].t >=0)
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

t_ray trnsform_ray(t_ray r, t_matrix *m)
{
	t_ray r2;
	
	r2.origin =  mul_matrix_tuple(m, r.origin);
	r2.direction =  mul_matrix_tuple(m, r.direction);
	return (r2);
}

void set_transform(t_shape *shape, t_matrix *m)
{
	shape->transform = m;
}