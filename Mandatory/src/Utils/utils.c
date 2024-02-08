/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 12:49:21 by ulysseclem        #+#    #+#             */
/*   Updated: 2024/02/08 18:38:05 by uclement         ###   ########.fr       */
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

float	d_to_r(float deg)
{
	return((deg / 180) * 3.141592);
}
void	swap(t_inter *xp, t_inter *yp)
{
	t_inter	temp;

	temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void	bubble_sort(t_inter *xs, int n)
{
	int		i;
	int		j;
	bool	swapped;

	swapped = false;
	i = 0;
	while (i < n - 1)
	{
		swapped = false;
		j = 0;
		while (j < n - i - 1)
		{
			if (xs[j].t > xs[j + 1].t)
			{
				swap(&xs[j], &xs[j + 1]);
				xs[j].count = n;
				swapped = true;
			}
			j++;
		}
		if (swapped == false)
			break ;
		i++;
	}
}