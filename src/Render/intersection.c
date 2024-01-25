/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:29:59 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/25 13:18:43 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_inter	create_inter_new(float t, t_shape shape)
{
	t_inter xs;

	xs.t = t;
	xs.shape = shape;
	xs.hit = false;
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


void swap(t_inter *xp, t_inter *yp) {
    t_inter temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(t_inter *xs, int n) // FOR TO FIX
{
    int i, j;
    bool swapped = false;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (xs[j].t > xs[j + 1].t) {
                swap(&xs[j], &xs[j + 1]);
				xs[j].count = n;
                swapped = true;
            }
        }
        if (swapped == false)
            break;
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
	if (size == 0)
		return (NULL);
	xs = malloc(sizeof(t_inter) * size);
	if (!xs)
		return (NULL);
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
	i = 0;
	while (i < size)
	{
		xs[i].count = size;
		i++;
	}
	bubbleSort(xs, size);
	return (xs);
}