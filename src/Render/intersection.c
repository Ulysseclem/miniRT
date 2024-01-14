/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:29:59 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 13:09:25 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_inter	create_inter_new(float t, t_shape shape)
{
	t_inter xs;

	xs.t = t;
	xs.shape = shape;
	return (xs);
}

int intersect_shape(t_shape *shape, t_ray ray)
{
	t_ray local_ray;
	t_matrix *inverted;

	inverted = inverse(shape->transform); // if NULL a gerer
	local_ray = trnsform_ray(ray, inverted);
	free_matrix(inverted);
	if (strcmp(shape->type, "sphere") == 0)
		shape->xs = sphere_intersect(shape, local_ray);
	// else if (strcmp(shape->type, "plane") == 0) 
	// 	shape->xs = plane_intersect(shape, local_ray)
	if (shape->xs != NULL)
		return(2);
	else
		return(0);
}

void	sort_inter(t_inter *xs, int size) // pas bon mais fonctionne pour le moment - ne fonctionnera pas si on veut faire des reflets
{
	t_inter tmp;
	int i;

	i = 0;
	while (i < size -1)
	{
		if (xs[i].t > xs[i + 1].t)
		{
			tmp = xs[i];
			xs[i] = xs[i +1];
			xs[i + 1] = tmp;
		}
		i++;
	}
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
	sort_inter(xs, size);
	return (xs);
}