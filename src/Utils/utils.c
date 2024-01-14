/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:49:21 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 13:09:59 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

/* ************************************************************************** */
/*					Magrnitude & norm pour normer des tuples				  */
/* ************************************************************************** */
float magnitude(t_tuple t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w);
}

t_tuple norm(t_tuple t)
{
	float mag = magnitude(t);

	if (mag != 0)
	{
		t.x = t.x / mag;
		t.y = t.y / mag;
		t.z = t.z / mag;
		t.w = t.w / mag;
	}
	return (t);
}

/* ************************************************************************** */
/*					Permet de verifier l'egalite des floats					  */
/* ************************************************************************** */
bool	equal(float a, float b)
{
	float epsilon;

	epsilon = 0.00001;
	if ((a - b) < epsilon)
		return true;
	else
		return false;
}

bool	equal_tuple(t_tuple a, t_tuple b)
{
	if (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z))
		return true;
	else
		return false;
}

void free_matrix(t_matrix *mat) 
{
    for (int i = 0; i < mat->r; i++) {
        free(mat->data[i]);
    }
    free(mat->data);
    free(mat);
}

float	d_to_r(float deg)  // converter degree to radian
{
	return((deg / 180) * 3.141592);
}