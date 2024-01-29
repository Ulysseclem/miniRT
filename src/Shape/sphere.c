/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/29 15:40:24 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_sphere sphere()
{
	t_sphere	s;
	static int	i = 0;

	// s.point = point(0, 0, 0);
	s.id = i;
	i++;
	return(s);
}

t_inter *sphere_intersect(t_shape *s, t_ray r) // inter de Sphere
{
	t_inter *xs;
	t_tuple s_t_r;
	int	size = 0;

	s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
	s->sphere.a = dot_product(r.direction, r.direction);
	s->sphere.b = dot_product(r.direction, s_t_r) * 2;
	s->sphere.c = dot_product(s_t_r, s_t_r) - 1;
	s->sphere.d = pow(s->sphere.b, 2) - (4 * s->sphere.a * s->sphere.c);
	if (s->sphere.d >= 0)
			size = 2;
	else
		return (NULL);
	xs = malloc(sizeof(t_inter) * size);
	if (!xs)
		return (NULL);
	xs[0] = create_inter_new(((s->sphere.b * -1) - sqrt(s->sphere.d)) / (2 * s->sphere.a), *s); // premiere inter
	xs[1] = create_inter_new(((s->sphere.b * -1) + sqrt(s->sphere.d)) / (2 * s->sphere.a), *s); // deuxieme inter
	return(xs);	
}

t_plane plane()
{
	static int i = 0;
	t_plane 	p;

	p.normal = vector(0,1,0);
	p.id = i;
	return (p);
}


t_inter *plane_intersect(t_shape *s, t_ray r)
{

	t_inter *xs;
	float	tmp_y;

	// print_tuple(r.origin);

	tmp_y = r.direction.y;
	if ( tmp_y < 0)
		tmp_y *=  -1;
	if (tmp_y < 0.00001)
		return (NULL);
	xs = malloc(sizeof(t_inter) * 2);
	// print_tuple(r.direction);
	xs[0] = create_inter_new(-r.origin.y/r.direction.y, *s);
	xs[1] = create_inter_new(-r.origin.y/r.direction.y, *s);
		// printf("t : %f", xs[0].t);
	return(xs);	
}

t_tuple plane_normal(t_plane p, t_tuple point)
{
	(void)point ;
	return (p.normal);
}