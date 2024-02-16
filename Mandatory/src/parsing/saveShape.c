/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveShape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:47 by uclement          #+#    #+#             */
/*   Updated: 2024/02/16 10:35:15 by icaharel         ###   ########.fr       */
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
	shape->transform = identify_matrix(4, 4);
	shape->ptr_type = plane;
	shape->type = PLANE;
	return (1);
}

void direction_to_degrees(float x_dir, float y_dir, float z_dir, float *x_deg, float *y_deg, float *z_deg) {
    // Calculate azimuth angle (rotation around z-axis)
    *z_deg = atan2(y_dir, x_dir) * 180.0 / PI;

    // Calculate elevation angle (angle above xy-plane)
    float xy_projection = sqrt(x_dir * x_dir + y_dir * y_dir);
    *x_deg = atan2(z_dir, xy_projection) * 180.0 / PI;

    // Calculate roll angle (rotation around x-axis)
    *y_deg = atan2(-x_dir * z_dir, xy_projection) * 180.0 / PI;
}

int	init_cy(char **param, t_shape *shape, t_world *world)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(cylinder));
	if (!cylinder)
		return (0);
	shape->point = str_to_point(param[1]);
	printf("%s\n", param[2]);
	shape->pl_dir = str_to_vector(param[2]);
	cylinder->diameter = ft_strtof(param[3]);
	cylinder->height = ft_strtof(param[4]);
	shape->material = str_to_material(param[5], world);
	shape->transform = identify_matrix(4,4);
	shape->ptr_type = cylinder;
	shape->type = CYLINDER;
	return (1);
}	
