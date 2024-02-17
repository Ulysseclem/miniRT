/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:47 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 16:42:06 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	init_sp(char **param, t_shape *shape, t_world *world)
{
	t_sphere	*sphere;

	sphere = malloc (sizeof(t_sphere));
	if (!sphere)
		return (0);
	shape->point = str_to_point(param[1]);
	sphere->diameter = ft_strtof(param[2]);
	shape->material = str_to_material(param[3], world);
	shape->transform = matrix_translation(shape->point.x, \
	shape->point.y, shape->point.z);
	shape->ptr_type = sphere;
	shape->type = SPHERE;
	return (1);
}

int	init_pl(char **param, t_shape *shape, t_world *world)
{
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (0);
	shape->point = str_to_point(param[1]);
	shape->pl_dir = str_to_vector(param[2]);
	shape->material = str_to_material(param[3], world);
	shape->transform = applies_movement(shape->pl_dir, shape->point);
	shape->ptr_type = plane;
	shape->type = PLANE;
	return (1);
}

int	init_cy(char **param, t_shape *shape, t_world *world)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (0);
	cylinder->height = ft_strtof(param[4]);
	cylinder->diameter = ft_strtof(param[3]);
	shape->pl_dir = str_to_vector(param[2]);
	shape->point = str_to_point(param[1]);
	shape->material = str_to_material(param[5], world);
	shape->transform = applies_movement(shape->pl_dir, shape->point);
	shape->ptr_type = cylinder;
	shape->type = CYLINDER;
	return (1);
}	