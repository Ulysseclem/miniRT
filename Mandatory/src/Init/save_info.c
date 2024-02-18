/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:58 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 12:50:18 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	init_light(char **param, t_world *w)
{
	w->l = light(str_to_point(param[1]), \
	mul_sca_color(set_color(1, 1, 1), ft_strtof(param[2], 1, 1.0, 0)));
	return (1);
}

int	init_ambiant(char **param, t_world *w)
{
	w->ambiant = mul_sca_color(str_to_color(param[2]), \
	ft_strtof(param[1], 1, 1.0, 0));
	return (1);
}

int	init_cam(char **param, t_camera *c)
{
	float		half_view;
	t_tuple		pos;
	t_tuple		orientation;

	c->hsize = WIDTH ;
	c->vsize = HEIGHT;
	half_view = tan(d_to_r(ft_strtof(param[3], 1, 1.0, 0)) / 2);
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

int	init_world(char **file, t_world *w)
{
	int		i;
	int		nshape;
	char	**line;
	t_shape	*s;

	i = 0;
	nshape = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "sp") == 0 || strcmp(line[0], "pl") == 0
			|| strcmp(line[0], "cy") == 0)
			nshape++;
		free_2(line);
		i++;
	}
	s = malloc(sizeof(t_shape) * nshape);
	if (!s)
		return (0);
	if (!search(file, &s, w))
		return (free(s), 0);
	w->shape = s;
	w->count = nshape;
	return (nshape);
}

int	init_camera(char **file, t_camera *c)
{
	int			i;
	int			ret;
	char		**line;

	i = 0;
	ret = 0;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (strcmp(line[0], "C") == 0)
		{
			ret = init_cam(line, c);
		}
		free_2(line);
		i++;
	}
	return (ret);
}
