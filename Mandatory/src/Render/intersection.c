/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:29:59 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/17 16:29:13 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_inter	create_inter_new(float t, t_shape shape)
{
	t_inter	xs;

	xs.t = t;
	xs.shape = shape;
	xs.hit = true;
	return (xs);
}

int	intersect_shape(t_shape *shape, t_ray ray)
{
	t_ray		local_ray;
	t_matrix	*inverted;

	inverted = inverse(shape->transform);
	local_ray = trnsform_ray(ray, inverted);
	free_matrix(inverted);
	if (shape->type == SPHERE)
		shape->xs = sphere_intersect(shape, local_ray);
	else if (shape->type == PLANE)
		shape->xs = plane_intersect(shape, local_ray);
	else if (shape->type == CYLINDER)
		shape->xs = cylinder_intersect(shape, local_ray);
	if (shape->xs != NULL)
		return (2);
	else
		return (0);
}

t_inter	*inter_world_2(t_world w, int size)
{
	int			i;
	int			j;
	t_inter		*xs;

	i = -1;
	j = 0;
	xs = malloc(sizeof(t_inter) * size);
	if (!xs)
		return (NULL);
	while (++i < w.count)
	{
		if (w.shape[i].xs != NULL)
		{
			xs[j] = w.shape[i].xs[0];
			xs[j + 1] = w.shape[i].xs[1];
			j = j + 2;
			free(w.shape[i].xs);
		}
	}
	i = -1;
	while (++i < size)
	{
		xs[i].count = size;
	}
	return (xs);
}

t_inter	*inter_world(t_world w, t_ray ray)
{
	int			i;
	int			size;
	t_inter		*xs;

	i = 0;
	size = 0;
	while (i < w.count)
	{
		size += intersect_shape(&(w.shape[i]), ray);
		i++;
	}
	if (size == 0)
		return (NULL);
	xs = inter_world_2(w, size);
	if (!xs)
		return (NULL);
	bubble_sort(xs, size);
	return (xs);
}
