/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   saveShape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:53:47 by uclement          #+#    #+#             */
/*   Updated: 2024/02/17 14:03:48 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

float calculate_rotation_y(t_tuple direction)
{
    return (atan2(direction.x, direction.z) *  (180.0f / PI));
}

float calculate_rotation_x(t_tuple direction)
{
    float angle;
    float magnitude;
    t_tuple normalized;
    
    magnitude = sqrt(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    normalized = vector(direction.x / magnitude, direction.y / magnitude, direction.z / magnitude);
    angle = acos(normalized.y);
    return (angle * (180.0f / PI));;
}

t_matrix *applies_movement(t_tuple direction, t_tuple position)
{
	float angle_x;
	float angle_y;
	t_matrix *rotX;
    t_matrix *rotY; 
    t_matrix *combined;
	
	angle_y = calculate_rotation_y(direction);
	rotY = matrix_rotation_y(angle_y);
    angle_x = calculate_rotation_x(direction);
    rotX = matrix_rotation_x(angle_x);
    combined = mul_matrix(rotY, rotX);
	return (mul_matrix(matrix_translation(position.x, position.y, position.z), combined));
}

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
	shape->transform = applies_movement(str_to_vector(param[2]), str_to_point(param[1]));
	//shape->transform = identify_matrix(4,4);
	shape->ptr_type = plane;
	shape->type = PLANE;
	return (1);
}

int	init_cy(char **param, t_shape *shape, t_world *world)
{
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(*cylinder));
	if (!cylinder)
		return (0);
	
	cylinder->height = ft_strtof(param[4]);
	cylinder->diameter = ft_strtof(param[3]);

	shape->pl_dir = str_to_vector(param[2]);  // a supp
	shape->point = str_to_point(param[1]); // a supp

	shape->material = str_to_material(param[5], world);  
    shape->transform  = applies_movement(str_to_vector(param[2]), str_to_point(param[1]));
    shape->ptr_type = cylinder;
	shape->type = CYLINDER;
	return (1);
}	
