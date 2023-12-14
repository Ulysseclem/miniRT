/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:26:14 by uclement          #+#    #+#             */
/*   Updated: 2023/12/14 16:16:18 by ulysseclem       ###   ########.fr       */
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

t_matrix *matrix_rotation_x(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	m->data[5] = cos(r);
	m->data[6] = sin(r) * -1;
	m->data[9] = sin(r);
	m->data[10] = cos(r);
	return (m);	
}

t_matrix *matrix_rotation_y(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	m->data[0] = cos(r);
	m->data[2] = sin(r);
	m->data[8] = sin(r) * -1;
	m->data[10] = cos(r);
	return (m);	
}

t_matrix *matrix_rotation_z(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	m->data[0] = cos(r);
	m->data[1] = sin(r) * -1;
	m->data[4] = sin(r);
	m->data[5] = cos(r);
	return (m);	
}
t_tuple matrix_rotation(t_tuple t, float x, float y, float z)
{
	if (x)
		t = mul_matrix_tuple(matrix_rotation_x(x), t);
	if (y != 0)
		t = mul_matrix_tuple(matrix_rotation_y(y), t);
	if (z != 0)
		t = mul_matrix_tuple(matrix_rotation_z(z), t);
	return (t); 
}

t_matrix *matrix_shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[1] = xy;
	m->data[2] = xz;
	m->data[4] = yx;
	m->data[6] = yz;
	m->data[8] = zx;
	m->data[9] = zy;
	return (m);	
}