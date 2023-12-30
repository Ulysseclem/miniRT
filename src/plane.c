/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:49:30 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/30 21:10:07 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


t_tuple	normale_at(t_shape shape, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	t_matrix	*inverted;
	t_matrix	*transposed;
	
	inverted = inverse(shape.transform);
	world_normal = vector(0, 0, 0);
	object_point = mul_matrix_tuple(inverted, world_point); // obtenir le point and object space
	object_normal = sub_tuple(object_point, world_normal);
	transposed = transp_matrix(inverted);
	world_normal = mul_matrix_tuple(transposed, object_normal);
	world_normal.w = 0;  // remettre le w a 0 (pour vecteur) car il risque d'avoir ete change.
	free_matrix(inverted);
	free_matrix(transposed);
	return(norm(world_normal));
}


t_inter	*sphere_intersect(t_shape shape, t_ray local_ray)
{
	t_inter *xs;
	float	a;
	float	b;
	float	c;
	float	d;
	t_tuple s_t_r;

	s_t_r = sub_tuple(local_ray.origin, point(0 ,0 , 0));
	a = dot_product(local_ray.direction, local_ray.direction);
	b = dot_product(local_ray.direction, s_t_r) * 2;
	c = dot_product(s_t_r, s_t_r) - 1;
	d = pow(b, 2) - (4 * a * c);   // si positif = touche l'objet
	if (d < 0)
		return (NULL);
	xs = malloc(sizeof(t_inter) * 2);
	if (!xs)
		return (NULL);
	xs[0] = create_inter(((b * -1) - sqrt(d)) / (2 * a), shape); // premiere inter
	xs[1] = create_inter(((b * -1) + sqrt(d)) / (2 * a), shape); // deuxieme inter
	xs->count = 2;
	shape.xs = xs;
	shape.xs->shape = &shape;
	return (xs);
}

t_shape	test_shape()
{
	t_shape shape;
	
	shape.transform = identify_matrix(4, 4);
	shape.material = material_default();
	shape.material.ambiant = 1;
	shape.content = "sphere";
	shape.xs = NULL;
	return(shape);
}

t_inter *intersect(t_shape shape, t_ray ray)
{
	t_ray 		local_ray;
	t_matrix	*inverted;

	inverted = inverse(shape.transform);
	local_ray = trnsform_ray(ray, inverted);
	shape.saved_ray = local_ray;
	free_matrix(inverted);
	if (strcmp(shape.content, "sphere") == 0)
		return(sphere_intersect(shape, local_ray));
	return (NULL);
}


void set_transform(t_shape *shape, t_matrix *m)
{
	shape->transform = m;
}


// SPHERE



t_inter *intersect_world(t_world w, t_ray ray)
{
	int i;
	int	j;
	int	k;
	int size;
	t_inter	*xs;
	t_inter	*xs_local;

	
	i = 0;
	size = 0;
	while (i < w.count) // permet de savoir le nombre d'intersection pour malloc + stock les inter dans les shapes
	{
		xs_local = intersect(w.shape[i], ray);
		if (xs_local)
		{
			size += xs_local[0].count;
			w.shape[i].xs = xs_local;
		}
		i++;
	}
	if (size == 0)
		return (NULL);
	xs = malloc(sizeof(t_shape) * size);
	i = 0;           
	k = 0;
	while (i < w.count) // Prends tous les intersections de chaque shape et les stocks dans une unique array de XS
	{
		j = 0;
		while (w.shape[i].xs && j < w.shape[i].xs->count)
		{
			xs[k] = w.shape[i].xs[j];
			j++;
			k++;
		}
		i++;
	}
	xs->count = size;
	sort_inter(xs);
	return(xs);
}


// t_inter	*intersect_world(t_world w, t_ray r2)
// {

// 	t_inter *xs;
// 	t_ray r;
// 	t_tuple s_t_r;
// 	xs = NULL;
// 	int i;
// 	int	test = 0;
// 	t_matrix	*inverted;

// 	i = 0;
// 	while (i < w.count)
// 	{	
// 		inverted = inverse(w.shape[i].transform); // retour NULL a gerer
// 		r = trnsform_ray(r2, inverted);
// 		free_matrix(inverted);
// 		s_t_r = sub_tuple(r.origin, point(0 ,0 , 0));
// 		w.s[i].a = dot_product(r.direction, r.direction);
// 		w.s[i].b = dot_product(r.direction, s_t_r) * 2;
// 		w.s[i].c = dot_product(s_t_r, s_t_r) - 1;
// 		w.s[i].d = pow(w.s[i].b, 2) - (4 * w.s[i].a * w.s[i].c);
// 		if (w.s[i].d >= 0)
// 			test += 2;
// 		i++;
// 	}
// 	if (test == 0)
// 		return (NULL);
// 	xs = malloc(sizeof(t_inter) * test);
// 	if (!xs)
// 		return (NULL);
// 	i = 0;
// 	int j = 0;
// 	xs[0].count = test;
// 	while (i < w.count)
// 	{
// 		if (w.s[i].d >= 0)
// 		{
// 			xs[j] = create_inter(((w.s[i].b * -1) - sqrt(w.s[i].d)) / (2 * w.s[i].a), w.s[i]); // premiere inter
// 			j++;
// 			xs[j] = create_inter(((w.s[i].b * -1) + sqrt(w.s[i].d)) / (2 * w.s[i].a), w.s[i]); // deuxieme inter
// 			j++;
// 		}
// 		i++;
// 	}
// 	xs->count = test;
// 	sort_inter(xs);
// 	return(xs);
// }
