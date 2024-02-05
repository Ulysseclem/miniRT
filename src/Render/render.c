/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:37:12 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/05 11:09:47 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

/* ************************************************************************** */
/*					gestion des couleurs									  */
/* ************************************************************************** */
int RGB_to_hex(t_color c) 
{
    long long int red, green, blue, hex_value;

    red = (long long int)(c.r * 255);
    green = (long long int)(c.g * 255);
    blue = (long long int)(c.b * 255);
    if (red < 0)
        red = 0;
    else if (red > 255)
        red = 255;
    if (green < 0)
        green = 0;
    else if (green > 255)
        green = 255;
    if (blue < 0)
        blue = 0;
    else if (blue > 255)
        blue = 255;
    hex_value = (red << 16) + (green << 8) + blue;
    return hex_value;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, t_color color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT)
		return;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = RGB_to_hex(color);
}

void	render(t_camera c, t_world w, t_data *img)
{
	int 	x;
	int 	y;
	t_color color;
	t_ray 	r;

	y = 0;
	while (y < c.vsize - 1)
	{
		x = 0;
		while (x < c.hsize - 1)
		{
			r = ray_for_pixel(c, x, y);
			color = color_at(w, r);
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}