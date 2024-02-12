/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:49:21 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/12 13:34:40 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

float	magnitude(t_tuple t)
{
	return (sqrt(t.x * t.x + t.y * t.y + t.z * t.z + t.w * t.w));
}

t_tuple	norm(t_tuple t)
{
	float	mag;

	mag = magnitude(t);
	if (mag != 0)
	{
		t.x = t.x / mag;
		t.y = t.y / mag;
		t.z = t.z / mag;
		t.w = t.w / mag;
	}
	return (t);
}

bool	equal(float a, float b)
{
	float	epsilon;

	epsilon = 0.00001;
	if ((a - b) < epsilon)
		return (true);
	else
		return (false);
}

bool	equal_tuple(t_tuple a, t_tuple b)
{
	if (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z))
		return (true);
	else
		return (false);
}

void	free_matrix(t_matrix *mat)
{
	int	i;

	i = 0;
	while (i < mat->r)
	{
		free(mat->data[i]);
		i++;
	}
	free(mat->data);
	free(mat);
}
