/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:13:20 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/03 15:25:50 by uclement         ###   ########.fr       */
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
	t_sphere *cur; //current
	
	cur = (t_sphere *)s->ptrType;

	s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
	cur->a = dot_product(r.direction, r.direction);
	cur->b = dot_product(r.direction, s_t_r) * 2;
	cur->c = dot_product(s_t_r, s_t_r) - 1;
	cur->d = pow(cur->b, 2) - (4 * cur->a * cur->c);
	if (cur->d >= 0)
			size = 2;
	else
		return (NULL);
	xs = malloc(sizeof(t_inter) * size);
	if (!xs)
		return (NULL);
	xs[0] = create_inter_new(((cur->b * -1) - sqrt(cur->d)) / (2 * cur->a), *s); // premiere inter
	xs[1] = create_inter_new(((cur->b * -1) + sqrt(cur->d)) / (2 * cur->a), *s); // deuxieme inter
	return(xs);	
}

t_inter *plane_intersect(t_shape *s, t_ray r)
{

	t_inter *xs;
	float	tmp_y;

	tmp_y = r.direction.y;
	if ( tmp_y < 0)
		tmp_y *=  -1;
	if (tmp_y < 0.00001)
		return (NULL);
	xs = malloc(sizeof(t_inter) * 2);
	xs[0] = create_inter_new(-r.origin.y/r.direction.y, *s);
	xs[1] = create_inter_new(-r.origin.y/r.direction.y, *s);
	return(xs);	
}

// t_tuple plane_normal(t_plane p, t_tuple point)
// {
// 	(void)point ;
// 	return (p.normal);
// }