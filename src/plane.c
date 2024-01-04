/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysse <ulysse@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 12:49:30 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/04 18:01:18 by ulysse           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	test_shape()
{
	t_shape shape;
	
	shape.transform = identify_matrix(4, 4);
	shape.material = material_default();
	return(shape);
}

t_tuple	normale_at(t_shape s, t_tuple world_point)
{
	t_tuple object_point;
	t_tuple object_normal;
	t_tuple world_normal;
	t_matrix	*inverted;
	t_matrix	*transposed;
	
	inverted = inverse(s.transform);

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

t_inter	create_inter_new(float nbr, t_shape shape)
{
	t_inter xs;

	xs.t = nbr;
	xs.shape = shape;
	xs.count = 1;
	return (xs);
}

t_inter *local_intersect(t_shape *s, t_ray r) // inter de Sphere
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
	xs->count = 2;
	return(xs);	
}


int intersect_shape(t_shape *shape, t_ray ray)
{
	t_ray local_ray;
	t_matrix *inverted;

	inverted = inverse(shape->transform); // if NULL a gerer
	local_ray = trnsform_ray(ray, (inverted));
	free_matrix(inverted);
	shape->xs = local_intersect(shape, local_ray);
	if (shape->xs != NULL)
		return(2);
	else
		return(0);
}

void	print_xs(t_inter *xs)
{
	int	i;
	i = 0;
	while (i < xs->count)
	{
		printf("xs : %f\n", xs[i].t);
		i++;
	}
}

t_inter* sort_inter(t_inter *xs, int size) 
{
    if (xs == NULL || size <= 1) {
        return xs; // No need to sort if array is empty or has only one element
    }
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (xs[j].t > xs[j + 1].t) {
                t_inter temp = xs[j];
                xs[j] = xs[j + 1];
                xs[j + 1] = temp;
            }
        }
    }
    return xs;
}

t_inter	*inter_world(t_world w, t_ray ray)
{
	int	i;
	int	j;
	int	size;
	t_inter	*xs;

	i = 0;
	size = 0;
	while (i < w.count)
	{
		size += intersect_shape(&(w.shape[i]), ray);	
		i++;
	}
	xs = malloc(sizeof(t_inter) * size);
	i = 0;
	j = 0;
	while (i < w.count)
	{
		if (w.shape[i].xs != NULL)
		{
			xs[j] = w.shape[i].xs[0];
			xs[j + 1] = w.shape[i].xs[1];
			j = j + 2;
			free(w.shape[i].xs);
		}
		i++;
	}
	xs->count = size;
	xs = sort_inter(xs, xs->count);
	return (xs);
}