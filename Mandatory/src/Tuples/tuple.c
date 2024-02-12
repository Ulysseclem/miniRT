/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:34:57 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/12 13:11:23 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

/* ************************************************************************** */
/*					Cree les tuples Point & Vecteur							  */
/* ************************************************************************** */
t_tuple	point(float x, float y, float z)
{
	t_tuple	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1;
	return (p);
}

t_tuple	vector(float x, float y, float z)
{
	t_tuple	v;

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
	t_tuple	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	return (c);
}

t_tuple	sub_tuple(t_tuple a, t_tuple b)
{
	t_tuple	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}
