/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:58 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 14:26:33 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	init_light(char **param, t_world *w)
{
	t_tuple	position;
	int		ret;

	ret = 1;
	position = str_to_point(param[1], &ret);
	if (!ret)
		return (0);
	w->l = light(position, mul_sca_color(set_color(1, 1, 1), \
	ft_strtof(param[2], 1, 1.0, 0)));
	return (1);
}

int	init_ambiant(char **param, t_world *w)
{
	int		ret;
	t_color	color_input;

	ret = 1;
	color_input = str_to_color(param[2], &ret);
	if (!ret)
		return (0);
	w->ambiant = mul_sca_color(color_input, ft_strtof(param[1], 1, 1.0, 0));
	return (1);
}

int	init_cam(char **param, t_camera *c)
{
	int			ret;
	float		half_view;
	t_tuple		pos;
	t_tuple		orient;

	ret = 1;
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
	pos = str_to_point(param[1], &ret);
	orient = str_to_point(param[2], &ret);
	if (ret == 0)
		return (0);
	c->transform = view_transform(pos, add_tuple(orient, pos), vector(0, 1, 0));
	return (1);
}

int	init_camera(char **file, t_camera *c)
{
	int			i;
	int			ret;
	char		**line;

	i = 0;
	ret = 1;
	while (file[i])
	{
		line = ft_split(file[i], ' ');
		if (ft_strcmp(line[0], "C") == 0)
		{
			ret = init_cam(line, c);
		}
		free_2(line);
		if (!ret)
			return (0);
		i++;
	}
	return (1);
}
