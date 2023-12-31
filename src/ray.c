/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 13:49:48 by uclement          #+#    #+#             */
/*   Updated: 2023/12/30 21:09:33 by ulysseclem       ###   ########.fr       */
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
	s.id = i;
	i++;
	return(s);
}
/* ************************************************************************** */
/*					END TEST SPHERE											  */
/* ************************************************************************** */

t_inter	create_inter(float t, t_shape s)
{
	t_inter i;
	
	i.t = t;
	i.shape = &s;

	return (i);
}

void ray(t_ray *r, t_tuple p, t_tuple v)
{
	r->origin = p;
	r->direction = v;
}

t_tuple position_f(t_ray r, float t)
{
	return (add_tuple(r.origin, mul_sca_tuple(r.direction, t)));
}

// t_inter	*intersect(t_sphere s, t_ray r2)
// {
// 	t_inter *xs;
// 	t_ray r;
// 	t_tuple s_t_r;
// 	xs = NULL;


// 	r = trnsform_ray(r2, inverse(s.transform));
// 	s.saved_ray = r;
// 	print_tuple(r.origin);
// 	s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
// 	a = dot_product(r.direction, r.direction);
// 	b = dot_product(r.direction, s_t_r) * 2;
// 	c = dot_product(s_t_r, s_t_r) - 1;
// 	d = pow(b, 2) - (4 * a * c);   // si positif = touche l'objet
// 	if (d < 0)
// 		return (NULL);
// 	xs = malloc(sizeof(t_inter) * 2);
// 	if (!xs)
// 		return (NULL);
// 	xs->count = 2;
// 	xs[0] = create_inter(((b * -1) - sqrt(d)) / (2 * a), s); // premiere inter
// 	xs[1] = create_inter(((b * -1) + sqrt(d)) / (2 * a), s); // deuxieme inter
// 	return(xs);
// }


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
	while(i < xs[0].count)
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


/* ************************************************************************** */
/*	Stock les interseciton dans une liste	A REVOIR EN ENTIER AVEC INTERSECT */
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
	xs->count = count;
	return (xs);
}

t_ray trnsform_ray(t_ray r, t_matrix *m)
{
	t_ray r2;
	
	r2.origin =  mul_matrix_tuple(m, r.origin);
	r2.direction =  mul_matrix_tuple(m, r.direction);
	return (r2);
}

// void set_transform(t_sphere *sphere, t_matrix *m)
// {
// 	sphere->transform = m;
// }