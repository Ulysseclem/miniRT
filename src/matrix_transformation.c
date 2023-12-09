/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:26:14 by uclement          #+#    #+#             */
/*   Updated: 2023/12/09 18:00:09 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix *matrix_translation(float x, float y, float z)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[3] = x;
	m->data[7] = y;
	m->data[11] = z;
	return (m);
}
t_matrix *matrix_scaling(float x, float y, float z)
{
	t_matrix	*m;

	m = identify_matrix(4, 4);
	m->data[0] = x;
	m->data[5] = y;
	m->data[10] = z;
	return (m);
}
float	d_to_r(float deg)  // converter degree to radian
{
	return((deg / 180) * 3.141592);
}

t_matrix *matrix_rotation_x(float r)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[5] = cos(r);
	m->data[6] = sin(r) * -1;
	m->data[9] = sin(r);
	m->data[10] = cos(r);
	return (m);	
}

t_matrix *matrix_rotation_y(float r)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[0] = cos(r);
	m->data[9] = sin(r) * -1;
	m->data[2] = sin(r);
	m->data[11] = cos(r);
	return (m);	
}

t_matrix *matrix_rotation_z(float r)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[0] = cos(r);
	m->data[1] = sin(r) * -1;
	m->data[2] = sin(r);
	m->data[3] = cos(r);
	return (m);	
}
