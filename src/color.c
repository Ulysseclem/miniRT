/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 19:21:49 by ulysseclem        #+#    #+#             */
/*   Updated: 2023/12/18 14:59:03 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	set_color(float x, float y, float z)
{
	t_color p;
	
	p.r = x;
	p.g = y;
	p.b = z;
	return (p);
}

t_color	add_color(t_color a, t_color b)
{
	t_color c;
	
	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return(c);
}

t_color	sub_color(t_color a, t_color b)
{
	t_color c;
	
	c.r = a.r - b.r;
	c.g = a.g - b.g;
	c.b = a.b - b.b;
	return(c);
}

t_color	mul_sca_color(t_color a, float mul)
{
	a.r *= mul;
	// printf("mul :%f, r = %f", mul, a.r);
	a.g *= mul;
	a.b *= mul;
	return (a);	
}

t_color	mul_color(t_color a, t_color b)
{
	t_color c;
	
	c.r = a.r * b.r;
	c.g = a.g * b.g;
	c.b = a.b * b.b;
	return(c);
}