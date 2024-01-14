/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ulysseclem <ulysseclem@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:34:57 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/01/14 13:09:50 by ulysseclem       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

/* ************************************************************************** */
/*					Cree les tuples Point & Vecteur							  */
/* ************************************************************************** */
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
	v.w = 0;
	return (v);
}

/* ************************************************************************** */
/*					Arithmetie de Tuple (+, -, *, neg)						  */
/* ************************************************************************** */
t_tuple	add_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	// if (c.w == 2)
	// {
	// 	perror("w = 2");
	// 	exit(1);
	// }
	return(c);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;
	
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
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
	a.y *= mul;
	a.z *= mul;
	a.w *= mul;
	return (a);	
}

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

	nbr = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	return (nbr);
}