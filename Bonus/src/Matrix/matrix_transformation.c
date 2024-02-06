/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:26:14 by uclement          #+#    #+#             */
/*   Updated: 2024/02/04 16:39:11 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"


t_matrix *matrix_translation(float x, float y, float z)
{
	t_matrix	*m;
	
	m = identify_matrix(4, 4);
	m->data[0][3] = x; // 3
	m->data[1][3] = y; //7
	m->data[2][3] = z; // 11
	return (m);
}
t_matrix *matrix_scaling(float x, float y, float z)
{
	t_matrix	*m;

	m = identify_matrix(4, 4);
	m->data[0][0] = x;
	m->data[1][1] = y; // 5
	m->data[2][2] = z; // 10
	return (m);
}

t_matrix *matrix_rotation_x(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	if (d == 0)
		return(m);
	m->data[1][1] = cos(r);      //5
	m->data[1][2] = sin(r) * -1; //6
	m->data[2][1] = sin(r); //9
	m->data[2][2] = cos(r); // 10
	return (m);	
}

t_matrix *matrix_rotation_y(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	if (d == 0)
		return(m);
	m->data[0][0] = cos(r);
	m->data[0][2] = sin(r);
	m->data[2][0] = sin(r) * -1;
	m->data[2][2] = cos(r);

	return (m);	
}

t_matrix *matrix_rotation_z(float d)
{
	t_matrix	*m;
	float		r;
	
	r = d_to_r(d);
	m = identify_matrix(4, 4);
	if (d == 0)
		return(m);
	m->data[0][0] = cos(r);
	m->data[0][1] = sin(r) * -1;
	m->data[1][0] = sin(r);
	m->data[1][1] = cos(r);
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
	m->data[0][1] = xy;
	m->data[0][2] = xz;
	m->data[1][0] = yx;
	m->data[1][2] = yz;
	m->data[2][0] = zx;
	m->data[2][1] = zy;
	return (m);	
}