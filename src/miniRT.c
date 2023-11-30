/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:49:57 by uclement          #+#    #+#             */
/*   Updated: 2023/11/30 16:12:37 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple cross_product(t_tuple a, t_tuple b)
{
	t_tuple c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return(c);
}

float dot_product(t_tuple a, t_tuple b)
{
	float nbr;

	nbr = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (nbr);
}

float magnitude(t_tuple t)
{
	return sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
}

t_tuple norm(t_tuple t)
{
	float mag = magnitude(t);

	if (mag != 0) {
		t.x /= mag;
		t.y /= mag;
		t.z /= mag;
	}
	return (t);
}

t_tuple	point(float x, float y, float z)
{
	t_tuple p;
	
	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1;
	return (p);
}

t_tuple	vector(float x, float y, float z)
{
	t_tuple v;
	
	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 1;
	return (v);
}

t_tuple	add_tuple(t_tuple a, t_tuple b, int mode)
{
	t_tuple c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	if (mode)
		c.w = a.w + b.w;
	// if (c.w == 2)
	// {
	// 	perror("w = 2");
	// 	exit(1);
	// }
	return(c);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b, int mode)
{
	t_tuple c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	if (mode)
		c.w = a.w - b.w;
	// if (c.w == -1)
	// {
	// 	perror("w = -1");
	// 	exit(1);
	// }
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
	// a.w *= mul; pas sur de celui la
	return (a);	
}
t_tuple	mul_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return(c);
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

t_proj tick(t_env env, t_proj proj)
{
	t_proj	new_proj;

	new_proj.pos = add_tuple(proj.pos, proj.vel);
	new_proj.vel = add_tuple(add_tuple(proj.vel, env.grav), env.wind);
	return (new_proj);
}

int main(void)
{
	t_proj	p;
	t_env	e;
	int		count = 0;

	p.pos = point(0, 1, 0);
	p.vel = vector(1, 1, 0);
	e.grav = vector(0, -0.1, 0);
	e.wind = vector(-0.01, 0, 0);

	while (p.pos.y > 0)
	{
		p = tick(e, p);
		count++;
		printf("%d\n", count);
	}
	return(0);
}