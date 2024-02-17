/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:26:52 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/08 18:12:09 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;
	t_matrix	*orientation;

	forward = norm(sub_tuple(to, from));
	left = norm(cross_product(forward, norm(up)));
	true_up = cross_product(left, forward);
	orientation = identify_matrix(4, 4);
	orientation->data[0][0] = left.x;
	orientation->data[0][1] = left.y;
	orientation->data[0][2] = left.z;
	orientation->data[1][0] = true_up.x;
	orientation->data[1][1] = true_up.y;
	orientation->data[1][2] = true_up.z;
	orientation->data[2][0] = -forward.x;
	orientation->data[2][1] = -forward.y;
	orientation->data[2][2] = -forward.z;
	return (mul_matrix(orientation, \
	matrix_translation(-from.x, -from.y, -from.z)));
}

t_camera	camera(int hsize, int vsize, float fov)
{
	t_camera	c;
	float		half_view;
	float		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.fov = fov;
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

t_ray	ray_for_pixel(t_camera c, float px, float py)
{
	float		world_y;
	t_tuple		origin;
	t_tuple		pixel;
	t_ray		r;
	t_matrix	*inverted;

	world_y = c.half_height - (py + 0.5) * c.pixel_size;
	inverted = inverse(c.transform);
	pixel = mul_matrix_tuple(inverted, point(c.half_width - (px + 0.5) * \
	c.pixel_size, world_y, -1));
	origin = mul_matrix_tuple(inverted, point(0, 0, 0));
	free_matrix(inverted);
	ray(&r, origin, norm(sub_tuple(pixel, origin)));
	return (r);
}
