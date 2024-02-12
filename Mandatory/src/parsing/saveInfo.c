/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveInfo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:58 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 12:53:27 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_light	light(t_tuple position, t_color color)
{
	t_light	l;

	l.position = position;
	l.color = color;
	return (l);
}

int	init_light(char **param, t_world *w)
{
	w->l = light(str_to_point(param[1]), \
	mul_sca_color(set_color(1, 1, 1), ft_strtof(param[2])));
	return (1);
}

int	init_ambiant(char **param, t_world *w)
{
	w->ambiant = mul_sca_color(str_to_color(param[2]), ft_strtof(param[1]));
	return (1);
}

int	init_cam(char **param, t_camera *c)
{
	float		half_view;
	t_tuple		pos;
	t_tuple		orientation;

	c->hsize = WIDTH ;
	c->vsize = HEIGHT;
	half_view = tan(d_to_r(ft_strtof(param[3])) / 2);
	if ((c->hsize / c->vsize) >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / (c->hsize / c->vsize);
	}
	else
	{
		c->half_width = half_view * (c->hsize / c->vsize);
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
	pos = str_to_point(param[1]);
	orientation = str_to_point(param[2]);
	orientation.x += pos.x;
	orientation.y += pos.y;
	orientation.z += pos.z;
	c->transform = view_transform(pos, orientation, vector(0, 1, 0));
	return (1);
}
