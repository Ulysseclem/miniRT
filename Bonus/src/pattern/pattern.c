/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:29:39 by uclement          #+#    #+#             */
/*   Updated: 2024/02/06 12:36:42 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

t_pattern stripe_pattern(t_color a, t_color b)
{
	t_pattern pat;

	pat.a = a;
	pat.b = b;
	return (pat);
}

t_color stripe_at(t_pattern pat, t_tuple point)
{
	if (point.x >= 0 && (int)point.x % 2 == 0)
		return (pat.a);
	else if (point.x < 0 && (int)floor(point.x) % 2 == 0)
		return(pat.a);
	else
		return(pat.b);
}

t_color stripe_at_object(t_pattern pat, t_shape s, t_tuple world_p)
{
	t_tuple object_p;
	t_tuple pattern_p;
	t_matrix *inverted;

	inverted = inverse(s.transform);
	object_p = mul_matrix_tuple(inverted, world_p);
	pattern_p = mul_matrix_tuple(inverted, object_p);
	free(inverted);
	return (stripe_at(pat, pattern_p));
}