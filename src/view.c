/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:26:52 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/17 17:46:15 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple 	forward;
	t_tuple 	left;
	t_tuple 	true_up;
	t_matrix	*orientation;
	
	forward = norm(sub_tuple(to, from));
	left = cross_product(forward, norm(up));
	true_up = cross_product(left, forward);
	orientation = identify_matrix(4, 4);
	orientation->data[0] = left.x;
	orientation->data[1] = left.y;
	orientation->data[2] = left.z;
	orientation->data[4] = true_up.x;
	orientation->data[5] = true_up.y;
	orientation->data[6] = true_up.z;
	orientation->data[8] = -forward.x;
	orientation->data[9] = -forward.y;
	orientation->data[10] = -forward.z;
	print_matrix(orientation);
	printf("\n");
	return(mul_matrix(orientation, matrix_translation(-from.x, -from.y, -from.z)));
}

t_camera	camera(int hsize, int vsize, float fov)
{
	t_camera c;
	float		half_view;
	float		aspect;
	
	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
	c.transform = identify_matrix(4, 4);
	half_view = tan(fov / 2);
	aspect = c.hsize / c.vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;	
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}