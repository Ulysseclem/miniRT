/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:37:12 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/29 15:58:15 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


/* ************************************************************************** */
/*					gestion des couleurs									  */
/* ************************************************************************** */
int RGB_to_hex(t_color c) 
{
	long long int red;
	long long int green;
	long long int blue;
	long long int hex_value;

	red = (long long int)(c.r * 255);
	green = (long long int)(c.g * 255);
	blue = (long long int)(c.b * 255);
	red = (red < 0) ? 0 : (red > 255) ? 255 : red;
	green = (green < 0) ? 0 : (green > 255) ? 255 : green;
	blue = (blue < 0) ? 0 : (blue > 255) ? 255 : blue;
	hex_value = (red << 16) + (green << 8) + blue;
	return (hex_value);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT)
	{
		printf("pixel out of bound");
		return;
	}
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = RGB_to_hex(color);
}

void	render(t_camera c, t_world w, t_data *img)
{
	int 	x;
	int 	y;
	t_color color;
	t_ray 	r;


	(void) img;
	y = 0;
	while (y < c.vsize - 1)
	{
		x = 0;
		while (x < c.hsize - 1)
		{
			r = ray_for_pixel(c, x, y);
			color = color_at(w, r);
			if (x == 0 && y == 0)
			{
				// exit(0);
			}
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}