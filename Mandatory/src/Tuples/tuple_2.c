/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:01 by uclement          #+#    #+#             */
/*   Updated: 2024/02/12 13:13:42 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_tuple	neg_tuple(t_tuple a)
{	
	a.x *= -1;
	a.y *= -1;
	a.z *= -1;
	a.w *= -1;
	return (a);
}

t_tuple	mul_sca_tuple(t_tuple a, float mul)
{
	a.x *= mul;
	a.y *= mul;
	a.z *= mul;
	a.w *= mul;
	return (a);
}

t_tuple	cross_product(t_tuple a, t_tuple b)
{
	t_tuple	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

float	dot_product(t_tuple a, t_tuple b)
{
	float	nbr;

	nbr = (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	return (nbr);
}
