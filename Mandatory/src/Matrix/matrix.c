/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uclement <uclement@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:43:53 by uclement          #+#    #+#             */
/*   Updated: 2024/02/08 17:42:48 by uclement         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "struct.h"

int	equal_matrix(t_matrix *a, t_matrix *b)
{
	int	i;
	int	j;

	if (a->c != b->c || a->r != b->r)
		return (0);
	i = 0;
	while (i < a->r)
	{
		j = 0;
		while (j < a->c)
		{
			if (!equal(a->data[i][j], b->data[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_matrix	*mul_matrix(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;
	int			i;
	int			j;
	int			k;
	float		sum;

	result = create_matrix(a->r, b->c);
	i = -1;
	while (++i < a->r)
	{
		j = -1;
		while (++j < b->c)
		{
			k = -1;
			sum = 0;
			while (++k < a->c)
			{
				sum += a->data[i][k] * b->data[k][j];
			}
			result->data[i][j] = sum;
		}
	}
	free_matrix(a);
	free_matrix(b);
	return (result);
}

t_tuple	mul_matrix_tuple(t_matrix *a, t_tuple b)
{
	t_tuple		result;	

	result.x = a->data[0][0] * b.x + a->data[0][1] \
	* b.y + a->data[0][2] * b.z + a->data[0][3] * b.w;
	result.y = a->data[1][0] * b.x + a->data[1][1] \
	* b.y + a->data[1][2] * b.z + a->data[1][3] * b.w;
	result.z = a->data[2][0] * b.x + a->data[2][1] \
	* b.y + a->data[2][2] * b.z + a->data[2][3] * b.w;
	result.w = a->data[3][0] * b.x + a->data[3][1] \
	* b.y + a->data[3][2] * b.z + a->data[3][3] * b.w;
	return (result);
}

t_matrix	*transp_matrix(t_matrix *m)
{
	t_matrix	*transpose;
	int			i;
	int			j;

	transpose = create_matrix(m->r, m->c);
	if (!transpose)
		return (NULL);
	i = 0;
	while (i < m->r)
	{
		j = 0;
		while (j < m->c)
		{
			transpose->data[i][j] = m->data[j][i];
			j++;
		}
		i++;
	}
	return (transpose);
}
