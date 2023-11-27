/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/11/27 15:09:45 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


#include <math.h>


float magnitude(t_tuple t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
}

t_tuple normalizeTuple(t_tuple t)
{
	float mag = magnitude(t);

	if (mag != 0) {
		t.x /= mag;
		t.y /= mag;
		t.z /= mag;
	}
	return t;
}

void	point(float x, float y, float z, t_tuple *point)
{
	point->x = x;
	point->y = y;
	point->z = z;
	point->w = 1;
}

void	vector(float x, float y, float z, t_tuple *vector)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
	vector->w = 0;
}

t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	if (c.w == 2)
	{
		perror("w = 2");
		exit(1);
	}
	return(c);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
	if (c.w == -1)
	{
		perror("w = -1");
		exit(1);
	}
	return(c);
}
t_tuple	neg_tuple(t_tuple a)
{	
	a.x *= -1;
	a.y *= -1;
	a.z *= -1;
	a.w *= -1;
	return(a);
}

t_tuple	mul_sca_tuple(t_tuple a, float mul)
{
	a.x *= mul;
	a.x *= mul;
	a.z *= mul;
	a.w *= mul; //pas sur de celui la
	return (a);	
}

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


int main(void)
{
	t_tuple	a;
	t_tuple	b;
	
	point(1, 2 , 3, &a);
	b = normalizeTuple(a);
	printf("%f\n", magnitude(b));
	return(0);
}