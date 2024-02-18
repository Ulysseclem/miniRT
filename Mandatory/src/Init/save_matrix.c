/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icaharel <icaharel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:47:58 by uclement          #+#    #+#             */
/*   Updated: 2024/02/18 10:57:17 by icaharel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

float	calculate_rotation_y(t_tuple direction)
{
	return (atan2(direction.x, direction.z) * (180.0f / PI));
}

float	calculate_rotation_x(t_tuple direction)
{
	t_tuple	normalized;

	normalized = norm(direction);
	return (acos(normalized.y) * (180.0f / PI));
}

t_matrix	*applies_movement(t_tuple direction, t_tuple pos)
{
	float		angle_x;
	float		angle_y;
	t_matrix	*rot_x;
	t_matrix	*rot_y;
	t_matrix	*combined;

	angle_y = calculate_rotation_y(direction);
	rot_y = matrix_rotation_y(angle_y);
	angle_x = calculate_rotation_x(direction);
	rot_x = matrix_rotation_x(angle_x);
	combined = mul_matrix(rot_y, rot_x);
	return (mul_matrix(matrix_translation(pos.x, pos.y, pos.z), combined));
}
