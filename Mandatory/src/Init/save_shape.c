/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:47 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 13:41:27 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	init_sp(char **param, t_shape *shape, t_world *world)
{
	t_sphere	*sphere;
	int			ret;

	ret = 1;
	sphere = malloc (sizeof(t_sphere));
	if (!sphere)
		return (0);
	sphere->diameter = ft_strtof(param[2], 1, 1.0, 0);
	shape->point = str_to_point(param[1], &ret);
	shape->material = str_to_material(param[3], world, &ret);
	if (ret == 0)
		return (free(sphere), 0);
	shape->transform = matrix_translation(shape->point.x, \
	shape->point.y, shape->point.z);
	shape->ptr_type = sphere;
	shape->type = SPHERE;
	return (1);
}

int	init_pl(char **param, t_shape *shape, t_world *world)
{
	t_plane	*plane;
	int		ret;

	ret = 1;
	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	shape->point = str_to_point(param[1], &ret);
	shape->pl_dir = str_to_vector(param[2], &ret);
	shape->material = str_to_material(param[3], world, &ret);
	if (ret == 0)
		return (free(plane), 0);
	shape->transform = applies_movement(shape->pl_dir, shape->point);
	shape->ptr_type = plane;
	shape->type = PLANE;
	return (1);
}

int	init_cy(char **param, t_shape *shape, t_world *world)
{
	t_cylinder	*cylinder;
	int			ret;

	ret = 1;
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->height = ft_strtof(param[4], 1, 1.0, 0);
	cylinder->diameter = ft_strtof(param[3], 1, 1.0, 0);
	shape->pl_dir = str_to_vector(param[2], &ret);
	shape->point = str_to_point(param[1], &ret);
	shape->material = str_to_material(param[5], world, &ret);
	if (ret == 0)
		return (free(cylinder), 0);
	shape->transform = applies_movement(shape->pl_dir, shape->point);
	shape->ptr_type = cylinder;
	shape->type = CYLINDER;
	return (1);
}	
