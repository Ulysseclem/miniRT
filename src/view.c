/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:26:52 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/18 14:31:54 by uclement         ###   ########.fr       */
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

t_ray	ray_for_pixel(t_camera c, float px, float py)
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_tuple	direction;
	t_tuple	origin;
	t_tuple	pixel;
	t_ray r;

	xoffset = (px + 0.5) * c.pixel_size; // +0.5 poura voir le centre du pixel
	yoffset = (py + 0.5) * c.pixel_size;
	world_x = c.half_width - xoffset; // ajuste le pixel par rapport a la camera
	world_y = c.half_height - yoffset;
	pixel = mul_matrix_tuple(inverse(c.transform), point(world_x, world_y, -1)); // -1 is for the nearest plan
	origin = mul_matrix_tuple(inverse(c.transform), point(0, 0, 0));
	direction = norm(sub_tuple(pixel, origin));
	ray(&r, origin, direction);
	
	return(r);
}
  #include <stdlib.h>
void	render(t_camera c, t_world w)
{
	int 	x;
	int 	y;
	t_color color;
	t_ray 	r;

	x = 5;
	y = 5;
	r = ray_for_pixel(c, x, y);
	color = color_at(w, r);
				print_color(color);

	// y = 0;
	// while (y < c.vsize - 1)
	// {
	// 	x = 0;
	// 	while (x < c.hsize - 1)
	// 	{
	// 		r = ray_for_pixel(c, x, y);
	// 		color = color_at(w, r);
	// 		// if (x == 1 && y == 1)
	// 		// {
	// 			print_color(color);
	// 			// exit(0);
	// 		// }
	// 		x++;
	// 	}
	// 	y++;
	// }
}